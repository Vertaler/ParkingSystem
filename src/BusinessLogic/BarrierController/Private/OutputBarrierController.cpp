#include "OutputBarrierController.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace Vertaler::ParkingSystem::BL::BarrierController
{

auto OutputBarrierController::tryPassVehicle(const Domain::Vehicle &vehicle, const Domain::TimePoint &time) const
  -> Cmn::Result<PassVehicleResult>
{
  Domain::ReleasingRequest req{ vehicle.number, time };
  auto res = getAccountService().releaseParkingSpace(req);
  if (auto *err = res.getError(); err != nullptr)
  {
    return PassVehicleResult{ false, { "Couldn't pass car" } };
  }

  const auto &paymentTicket = res.getResult();
  const auto printMessage = fmt::format("Parking price: {}", paymentTicket.parkingPrice.amount);
  return PassVehicleResult{ true, { printMessage } };
}

}// namespace Vertaler::ParkingSystem::BL::BarrierController