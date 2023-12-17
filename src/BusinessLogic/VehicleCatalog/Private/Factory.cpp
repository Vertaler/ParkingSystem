#include "VehicleCatalogImpl.h"

#include "BusinessLogic/VehicleCatalog/Public/Factory.h"

namespace Vertaler::ParkingSystem::BL::VehicleCatalog
{
std::unique_ptr<Interface> create()
{
  return std::make_unique<VehicleCatalogImpl>();
}
}// namespace Vertaler::ParkingSystem::BL::VehicleCatalog
