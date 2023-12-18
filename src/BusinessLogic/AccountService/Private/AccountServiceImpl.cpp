#include "AccountServiceImpl.h"

#include "BusinessLogic/AccountService/Public/Errors.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

Cmn::Result<Domain::ReservationTicket> AccountServiceImpl::reserveParkingSpace(const Domain::ReservationRequest &req)
{
  const auto &vehicleNumber = req.vehicle.number;
  Domain::ReservationTicket ticket{ vehicleNumber, req.arrivalTime };
  const Domain::ParkingReservation reservation{ vehicleNumber, req.arrivalTime };
  _reservationStorage[vehicleNumber] = reservation;
  return ticket;
}

Cmn::Result<Domain::ReleasingResponse> AccountServiceImpl::releaseParkingSpace(const Domain::ReleasingRequest &req)
{
  _reservationStorage.erase(req.vehicleNumber);
  return {};
}

Cmn::Result<Domain::ParkingReservation> AccountServiceImpl::getParkingReservation(
  const Domain::VehicleNumber &vehicleNumber) const
{
  if (auto iter = _reservationStorage.find(vehicleNumber); iter != _reservationStorage.end())
  {
    return { iter->second };
  }

  return { Cmn::Error(Errc::ReservationNotFound) };
}

}// namespace Vertaler::ParkingSystem::BL::AccountService