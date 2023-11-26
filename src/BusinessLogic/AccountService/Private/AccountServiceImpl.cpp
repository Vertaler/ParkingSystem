#include "AccountServiceImpl.h"
#include "Domain/PaymentTicket.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

AccountServiceImpl::AccountServiceImpl(const PriceCalculator::Interface &priceCalculator)
  : _priceCalculator(priceCalculator)
{}

Cmn::Result<Domain::ReservationTicket> AccountServiceImpl::reserveParkingSpace(const Domain::ReservationRequest &req)
{
  const auto &vehicleNumber = req.vehicle.number;
  Domain::ReservationTicket ticket{ vehicleNumber, req.arrivalTime };
  _storage[vehicleNumber.asString()] = ticket;
  return ticket;
}

Cmn::Result<Domain::PaymentTicket> AccountServiceImpl::releaseParkingSpace(const Domain::ReleasingRequest &req)
{
  if (auto iter = _storage.find(req.vehicleNumber.asString()); iter != _storage.end())
  {
    const auto reservationTicket = iter->second;
    _storage.erase(iter);
    auto price = _priceCalculator.calculateParkingPrice(reservationTicket, req.departureTime);
    return Domain::PaymentTicket{ price.getResult() };
  }
  return {};
}


}// namespace Vertaler::ParkingSystem::BL::AccountService