#include "InputBarrierController.h"

#include "Domain/ParkingReservation.h"

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace Vertaler::ParkingSystem::BL::BarrierController
{

auto InputBarrierController::tryPassVehicle(const Domain::Vehicle &vehicle, const Domain::TimePoint &time) const
  -> Cmn::Result<PassVehicleResult>
{
  Domain::ReservationRequest req{ vehicle, time };
  auto res = getAccountService().reserveParkingSpace(req);
  if (auto *err = res.getError(); err != nullptr)
  {
    return PassVehicleResult{ false, { "Couldn't pass car" } };
  }

  const auto &reservationTicket = res.getResult();
  const auto printMessage = fmt::format("ReservationTicket[VehicleNumber: {}|Time: {}]",
    reservationTicket.number.asString(),
    reservationTicket.arrivalTime);
  return PassVehicleResult{ true, { printMessage } };
}

}// namespace Vertaler::ParkingSystem::BL::BarrierController