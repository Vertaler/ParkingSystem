#pragma once

#include "BusinessLogic/AccountService/Public/InterfaceWithObserver.h"

#include "Domain/EntryExit.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Vehicle.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

class AccountServiceImpl final : public InterfaceWithObserver
{
public:
  Cmn::Result<Domain::ReservationTicket> reserveParkingSpace(const Domain::ReservationRequest &req) override;
  Cmn::Result<Domain::ReleasingResponse> releaseParkingSpace(const Domain::ReleasingRequest &req) override;
  [[nodiscard]] Cmn::Result<Domain::ParkingReservation> getParkingReservation(
    const Domain::VehicleNumber &vehicleNumber) const override;

  void onEntry(const Domain::EntryRequest &req) override;
  void onExit(const Domain::ExitRequest &req) override;

private:
  std::unordered_map<Domain::VehicleNumber, Domain::ParkingReservation> _reservationStorage;
};

}// namespace Vertaler::ParkingSystem::BL::AccountService