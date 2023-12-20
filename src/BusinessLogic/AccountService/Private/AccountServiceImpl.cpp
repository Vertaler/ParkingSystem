#include "AccountServiceImpl.h"

#include "BusinessLogic/AccountService/Public/Errors.h"

#include "Domain/ParkingReleasing.h"
#include "Domain/PaymentTicket.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

AccountServiceImpl::AccountServiceImpl(const PriceCalculator::Interface &priceCalculator,
  PaymentService::Interface &paymentService)
  : _priceCalculator(priceCalculator), _paymentService(paymentService)
{}

Cmn::Result<Domain::ReservationTicket> AccountServiceImpl::reserveParkingSpace(const Domain::ReservationRequest &req)
{
  const auto &vehicleNumber = req.vehicle.number;
  Domain::ReservationTicket ticket{ vehicleNumber, req.arrivalTime };
  _storage[vehicleNumber] = ticket;
  const auto paymentTicket = _paymentService.registerNewReservation(ticket);
  _paymentTicketsIDs.emplace(vehicleNumber, paymentTicket.getResult());
  return ticket;
}

Cmn::Result<Domain::ReleasingResponse> AccountServiceImpl::releaseParkingSpace(const Domain::ReleasingRequest &req)
{
  const auto &vehicleNumber = req.vehicleNumber;
  if (auto iter = _storage.find(vehicleNumber); iter != _storage.end())
  {
    const auto reservationTicket = iter->second;
    const auto &paymentTicketID = _paymentTicketsIDs.at(vehicleNumber);

    if (!_paymentService.needPay(paymentTicketID).getResult())
    {
      _paymentTicketsIDs.erase(vehicleNumber);
      _storage.erase(iter);

      return Domain::ReleasingResponse{ Domain::ReleasingStatus::OK, {} };
    }

    auto price = _priceCalculator.calculateParkingPrice(reservationTicket, req.departureTime);
    return Domain::ReleasingResponse{ Domain::ReleasingStatus::PaymentRequired,
      Domain::PaymentTicket{ price.getResult(), paymentTicketID } };
  }
  return Cmn::Error(Errc::ReservationNotFound);
}


}// namespace Vertaler::ParkingSystem::BL::AccountService