#pragma once

#include "Domain/ParkingSpaceInfo.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::Domain
{

struct ParkingReservation
{
  VehicleNumber number;
  TimePoint arrivalTime;
};


}// namespace Vertaler::ParkingSystem::Domain