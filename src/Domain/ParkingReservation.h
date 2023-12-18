#pragma once

#include "Domain/ParkingSpaceInfo.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"
#include <optional>

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

struct ParkingReservation
{
  VehicleNumber number;
  TimePoint arrivalTime;
};

using ParkingReservationOpt = std::optional<ParkingReservation>;


}// namespace Vertaler::ParkingSystem::Domain