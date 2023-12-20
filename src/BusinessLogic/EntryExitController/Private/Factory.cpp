#include "EntryExitControllerImpl.h"

#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/VehicleCatalog/Public/Interface.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
std::unique_ptr<Interface> create(PaymentService::Interface &paymentService, VehicleCatalog::Interface &vehicleCatalog)
{
  return std::make_unique<EntryExitControllerImpl>(paymentService, vehicleCatalog);
}
}// namespace Vertaler::ParkingSystem::BL::EntryExitController