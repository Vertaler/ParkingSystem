#include "EntryExitControllerImpl.h"
#include "Common/Error.h"

#include "Domain/EntryExit.h"
#include "VehicleServiceCategoryHelpers.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

EntryExitControllerImpl::EntryExitControllerImpl(PaymentService::Interface &paymentService,
  VehicleCatalog::Interface &vehicleCatalog)
  : _paymentSystem(paymentService), _vehicleCatalog(vehicleCatalog)
{}

Cmn::Result<Domain::EntryResponse> EntryExitControllerImpl::entry(const Domain::EntryRequest &req)
{
  for (auto &observer : _observers)
  {
    observer.get().onEntry(req);
  }
  return {};
}

Cmn::Result<Domain::ExitResponse> EntryExitControllerImpl::exit(const Domain::ExitRequest &req)
{
  auto vehicle = _vehicleCatalog.receiveVehicleInfo(req.vehicleNumber);
  CMN_HANDLE_DEPENDENCY_ERR(vehicle);

  const auto &vehicleRes = vehicle.getResult();

  Domain::ExitResponse result;
  // Always pass emergency services without payment
  if (isEmergencyService(vehicleRes.serviceCategory))
  {
    result.status = Domain::ExitStatus::OK;
  } else
  {
    auto payment = _paymentSystem.getPayment(req);
    CMN_HANDLE_DEPENDENCY_ERR(vehicle);

    const auto &paymentRes = payment.getResult();
    if (!paymentRes.has_value())
    {
      result.status = Domain::ExitStatus::OK;
    } else
    {
      result.status = Domain::ExitStatus::PaymentRequired;
      result.paymentTicket = *paymentRes;
    }
  }

  if (result.status == Domain::ExitStatus::OK)
  {
    for (auto &observer : _observers)
    {
      observer.get().onExit(req);
    }
  }
  return result;
}

void EntryExitControllerImpl::registerObserver(Observer &observer)
{
  _observers.emplace_back(observer);
}

}// namespace Vertaler::ParkingSystem::BL::EntryExitController