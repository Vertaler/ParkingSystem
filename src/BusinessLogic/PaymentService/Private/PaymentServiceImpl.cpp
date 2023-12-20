#include "PaymentServiceImpl.h"

#include "BusinessLogic/ParkingSpaceManager/Public/Errors.h"
#include "BusinessLogic/PaymentService/Public/Errors.h"

#include "Common/Error.h"
#include "Domain/PaymentTicket.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::PaymentService
{

namespace
{
  Domain::PaymentTicketID generateTicketID(const Domain::VehicleNumber &vehicleNumber)
  {
    return vehicleNumber.asString();
  }

}// namespace

PaymentServiceImpl::PaymentServiceImpl(PriceCalculator::Interface &priceCalculator,
  ParkingSpaceManager::Interface &parkingSpaceManager)
  : _priceCalculator(priceCalculator), _parkingSpaceManager(parkingSpaceManager)
{}

Cmn::Result<void> PaymentServiceImpl::pay(const Domain::PaymentTicketID &ticketID)
{
  auto iter = _unpdaidTickets.find(ticketID);
  if (iter == _unpdaidTickets.end())
  {
    return Cmn::Error(Errc::PaymentTicketNotFound);
  }

  _paidTickets.emplace(ticketID);
  return {};
}

Cmn::Result<Domain::PaymentTicketOpt> PaymentServiceImpl::getPayment(const Domain::ExitRequest &req) const
{
  auto paymentTicketID = generateTicketID(req.vehicleNumber);
  if (_paidTickets.contains(paymentTicketID))
  {
    return Domain::PaymentTicketOpt{};
  }

  if (const auto iter = _unpdaidTickets.find(paymentTicketID); iter != _unpdaidTickets.end())
  {
    return Domain::PaymentTicketOpt{ iter->second };
  }

  auto parkingReservation = _parkingSpaceManager.getParkingReservation(req.vehicleNumber);
  if (auto *err = parkingReservation.getError(); err != nullptr)
  {
    if (err->is(ParkingSpaceManager::Errc::ReservationNotFound))
    {
      // TODO log this;
      return Domain::PaymentTicketOpt{};
    }
    return CMN_NESTED_ERR(Cmn::Errc::DependencyError, err);
  }

  const auto &parkingReservationRes = parkingReservation.getResult();

  const auto departureTime = req.time;

  auto price = _priceCalculator.calculateParkingPrice(parkingReservationRes, departureTime);
  CMN_HANDLE_DEPENDENCY_ERR(price);

  Domain::PaymentTicket result;
  result.ID = std::move(paymentTicketID);
  result.parkingPrice = price.getResult();

  _unpdaidTickets.emplace(result.ID, result);

  return Domain::PaymentTicketOpt{ result };
}

};// namespace Vertaler::ParkingSystem::BL::PaymentService