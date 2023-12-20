#pragma once

#include "Domain/ParkingSpaceInfo.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::Domain
{

struct ReservationRequest
{
  Vehicle vehicle;
  TimePoint arrivalTime;
};

struct ReservationTicket
{
  VehicleNumber number;
  TimePoint arrivalTime;
};

}// namespace Vertaler::ParkingSystem::Domain