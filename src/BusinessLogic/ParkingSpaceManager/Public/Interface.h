#pragma once

#include "Common/Result.h"

#include "Domain/ParkingReservation.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{

class Interface
{
public:
  virtual ~Interface() = default;
  [[nodiscard]] virtual Cmn::Result<Domain::ParkingReservation> getParkingReservation(
    const Domain::VehicleNumber &vehicleNumber) const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager