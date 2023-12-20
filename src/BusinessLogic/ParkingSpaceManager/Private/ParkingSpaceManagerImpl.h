#pragma once

#include "BusinessLogic/ParkingSpaceManager/Public/InterfaceWithObserver.h"

#include "Domain/EntryExit.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Vehicle.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{

class ParkingSpaceManagerImpl final : public InterfaceWithObserver
{
public:
  [[nodiscard]] Cmn::Result<Domain::ParkingReservation> getParkingReservation(
    const Domain::VehicleNumber &vehicleNumber) const override;

  void onEntry(const Domain::EntryRequest &req) override;
  void onExit(const Domain::ExitRequest &req) override;

private:
  void reserveParkingSpace(const Domain::EntryRequest &req);
  void releaseParkingSpace(const Domain::ExitRequest &req);

private:
  std::unordered_map<Domain::VehicleNumber, Domain::ParkingReservation> _reservationStorage;
};

}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager