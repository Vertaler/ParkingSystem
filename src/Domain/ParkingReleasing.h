#pragma once

#include "Domain/Time.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::Domain
{

struct ReleasingRequest
{
  VehicleNumber vehicleNumber;
  TimePoint departureTime;
};

}// namespace Vertaler::ParkingSystem::Domain