#pragma once

#include <memory>

namespace Vertaler::ParkingSystem::BL::PaymentService
{
class Interface;
}

namespace Vertaler::ParkingSystem::BL::VehicleCatalog
{
class Interface;
}

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
class Interface;
std::unique_ptr<Interface> create(PaymentService::Interface &paymentService, VehicleCatalog::Interface &vehicleCatalog);

}// namespace Vertaler::ParkingSystem::BL::EntryExitController