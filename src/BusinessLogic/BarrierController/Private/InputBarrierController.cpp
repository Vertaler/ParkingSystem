#include "InputBarrierController.h"

#include "Domain/EntryExit.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

#include "Common/Result.h"

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace Vertaler::ParkingSystem::BL::BarrierController
{

auto InputBarrierController::tryPassVehicle(const Domain::VehicleNumber &vehicleNumber,
  const Domain::TimePoint &time) const -> Cmn::Result<PassVehicleResult>
{
  const Domain::EntryRequest req{ vehicleNumber, time };
  auto res = getEntryExitHandler().entry(req);
  if (auto *err = res.getError(); err != nullptr)
  {
    return PassVehicleResult{ false, { "Couldn't pass car" } };
  }

  if (auto *err = res.getError(); err != nullptr)
  {
    return PassVehicleResult{ false, "Error on entry" };
  }
  const auto printMessage = fmt::format("Entry allowed [VehicleNumber: {}|Time: {}]", vehicleNumber.asString(), time);
  return PassVehicleResult{ true, { printMessage } };
}

}// namespace Vertaler::ParkingSystem::BL::BarrierController