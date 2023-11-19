#pragma once

#include "Domain/CarInfo.h"
#include "Domain/ParkingSpaceInfo.h"
#include "Domain/Time.h"

namespace Vertaler::ParkingSystem::Domain
{

struct ReservationRequest
{
  CarInfo carInfo;
  ParkingSpaceInfo desiredParkingSpace;
};

struct ReservationTicket
{
  CarNumber number;
  TimePoint arrivalTime;
};

}// namespace Vertaler::ParkingSystem::Domain