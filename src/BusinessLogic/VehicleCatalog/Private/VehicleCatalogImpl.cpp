#include "VehicleCatalogImpl.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::VehicleCatalog
{
Cmn::Result<Domain::Vehicle> VehicleCatalogImpl::receiveVehicleInfo(const Domain::VehicleNumber &number) const
{
  Domain::Vehicle result;
  result.number = number;
  const auto numberStr = number.asString();
  if (numberStr.starts_with("police"))
  {
    result.serviceCategory = Domain::VehicleServiceCategory::Police;
  } else if (numberStr.starts_with("ambulance"))
  {
    result.serviceCategory = Domain::VehicleServiceCategory::Ambulance;
  } else
  {
    result.serviceCategory = Domain::VehicleServiceCategory::General;
  }
  return result;
}
}// namespace Vertaler::ParkingSystem::BL::VehicleCatalog
