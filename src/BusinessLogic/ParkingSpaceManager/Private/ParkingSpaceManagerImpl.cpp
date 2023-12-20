#include "ParkingSpaceManagerImpl.h"

#include "BusinessLogic/ParkingSpaceManager/Public/Errors.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{

Cmn::Result<Domain::ReservationTicket> ParkingSpaceManagerImpl::reserveParkingSpace(
  const Domain::ReservationRequest &req)
{
  const auto &vehicleNumber = req.vehicle.number;
  Domain::ReservationTicket ticket{ vehicleNumber, req.arrivalTime };
  const Domain::ParkingReservation reservation{ vehicleNumber, req.arrivalTime };
  _reservationStorage[vehicleNumber] = reservation;
  return ticket;
}

Cmn::Result<Domain::ReleasingResponse> ParkingSpaceManagerImpl::releaseParkingSpace(const Domain::ReleasingRequest &req)
{
  _reservationStorage.erase(req.vehicleNumber);
  return {};
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
  const Domain::ReservationRequest reserveReq{ {}, req.time };
  reserveParkingSpace(reserveReq);
}

void ParkingSpaceManagerImpl::onExit(const Domain::ExitRequest &req)
{
  const Domain::ReleasingRequest releaseReq{ req.vehicleNumber, req.time };
  releaseParkingSpace(releaseReq);
}


}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager