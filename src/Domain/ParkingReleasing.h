#pragma once

#include "Domain/ParkingReservation.h"
#include "Domain/Time.h"

namespace Vertaler::ParkingSystem::Domain
{

struct ReleasingRequest
{
  ReservationTicket ticket;
  TimePoint departureTime;
};

}// namespace Vertaler::ParkingSystem::Domain