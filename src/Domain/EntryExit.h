
#pragma once

#include "Domain/PaymentTicket.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::Domain
{

struct EntryExitRequest
{
  VehicleNumber vehicleNumber;
  TimePoint time;
};

using EntryRequest = EntryExitRequest;
using ExitRequest = EntryExitRequest;

enum class ExitStatus
{
  OK,
  PaymentRequired
};

struct ExitResponse
{
  ExitStatus status;
  std::optional<PaymentTicket> paymentTicket;
};

struct EntryResponse
{
};

}// namespace Vertaler::ParkingSystem::Domain