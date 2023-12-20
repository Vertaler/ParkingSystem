#include "OutputBarrierController.h"
#include "Domain/EntryExit.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace Vertaler::ParkingSystem::BL::BarrierController
{

auto OutputBarrierController::tryPassVehicle(const Domain::VehicleNumber &vehicleNumber,
  const Domain::TimePoint &time) const -> Cmn::Result<PassVehicleResult>
{
  const Domain::ExitRequest req{ vehicleNumber, time };
  auto res = getEntryExitHandler().exit(req);
  if (auto *err = res.getError(); err != nullptr)
  {
    return PassVehicleResult{ false, { "Couldn't pass car" } };
  }

  const auto &releasingResponse = res.getResult();
  if (releasingResponse.status == Domain::ExitStatus::OK)
  {
    return PassVehicleResult{ true, { "Bon Voyage!" } };
  } else if (releasingResponse.status == Domain::ExitStatus::PaymentRequired)
  {
    const auto &paymentTicket = *releasingResponse.paymentTicket;
    const auto printMessage = fmt::format(
      "Payment required! PaymentTickedID: {}. Parking price: {}", paymentTicket.ID, paymentTicket.parkingPrice.amount);
    return PassVehicleResult{ false, { printMessage } };
  }

  assert(false && "This branch must be unreachable, probably not all relesing statuses are handled");
}

}// namespace Vertaler::ParkingSystem::BL::BarrierController