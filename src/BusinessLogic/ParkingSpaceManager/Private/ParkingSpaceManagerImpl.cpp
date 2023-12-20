#include "ParkingSpaceManagerImpl.h"

#include "BusinessLogic/ParkingSpaceManager/Public/Errors.h"
#include "Domain/ParkingReservation.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{

void ParkingSpaceManagerImpl::reserveParkingSpace(const Domain::EntryRequest &req)
{
  const auto &vehicleNumber = req.vehicleNumber;
  const Domain::ParkingReservation reservation{ req.vehicleNumber, req.time };
  _reservationStorage[vehicleNumber] = reservation;
}

void ParkingSpaceManagerImpl::releaseParkingSpace(const Domain::ExitRequest &req)
{
  _reservationStorage.erase(req.vehicleNumber);
}

Cmn::Result<Domain::ParkingReservation> ParkingSpaceManagerImpl::getParkingReservation(
  const Domain::VehicleNumber &vehicleNumber) const
{
  if (auto iter = _reservationStorage.find(vehicleNumber); iter != _reservationStorage.end())
  {
    return { iter->second };
  }

  return { Cmn::Error(Errc::ReservationNotFound) };
}

void ParkingSpaceManagerImpl::onEntry(const Domain::EntryRequest &req)
{
  reserveParkingSpace(req);
}

void ParkingSpaceManagerImpl::onExit(const Domain::ExitRequest &req)
{
  releaseParkingSpace(req);
}


}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager