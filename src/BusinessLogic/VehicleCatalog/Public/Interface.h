#pragma once

#pragma once

#include "Common/Result.h"

#include "Domain/Vehicle.h"


namespace Vertaler::ParkingSystem::BL::VehicleCatalog
{
class Interface
{
public:
  virtual ~Interface() = default;

  [[nodiscard]] virtual Cmn::Result<Domain::Vehicle> receiveVehicleInfo(const Domain::VehicleNumber &number) const = 0;
};
}// namespace Vertaler::ParkingSystem::BL::VehicleCatalog
