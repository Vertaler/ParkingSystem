#pragma once

#include "BusinessLogic/EntryExitController/Public/Interface.h"
#include "BusinessLogic/EntryExitController/Public/Observer.h"

#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/VehicleCatalog/Public/Interface.h"


#include <functional>
#include <vector>

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

class EntryExitControllerImpl : public Interface
{
public:
  EntryExitControllerImpl(PaymentService::Interface &paymentService, VehicleCatalog::Interface &vehicleCatalog);

  Cmn::Result<Domain::EntryResponse> entry(const Domain::EntryRequest &req) override;
  Cmn::Result<Domain::ExitResponse> exit(const Domain::ExitRequest &req) override;
  void registerObserver(Observer &observer) override;

private:
  std::vector<std::reference_wrapper<Observer>> _observers;
  PaymentService::Interface &_paymentSystem;
  VehicleCatalog::Interface &_vehicleCatalog;
};

}// namespace Vertaler::ParkingSystem::BL::EntryExitController