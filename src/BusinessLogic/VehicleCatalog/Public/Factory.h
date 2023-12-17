#pragma once

#include <memory>

namespace Vertaler::ParkingSystem::BL::VehicleCatalog
{
class Interface;
std::unique_ptr<Interface> create();
}// namespace Vertaler::ParkingSystem::BL::VehicleCatalog
