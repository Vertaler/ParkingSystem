#pragma once

#include "Domain/PaymentTicket.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

#include <optional>

namespace Vertaler::ParkingSystem::Domain
{

enum class ReleasingStatus
{
  OK,
  PaymentRequired
};
struct ReleasingRequest
{
  VehicleNumber vehicleNumber;
  TimePoint departureTime;
};

struct ReleasingResponse
{
  ReleasingStatus status;
  std::optional<PaymentTicket> paymentTicket;
};

}// namespace Vertaler::ParkingSystem::Domain