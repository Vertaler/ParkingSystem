#include "PaymentServiceImpl.h"

#include "BusinessLogic/PaymentService/Public/Errors.h"

#include "Common/Error.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::PaymentService
{

namespace
{
  Domain::PaymentTicketID generateTicketID(const Domain::VehicleNumber &vehicleNumber)
  {
    return vehicleNumber.asString();
  }


  Domain::PaymentTicketID generateTicketID(const Domain::ReservationTicket &ticket)
  {
    return generateTicketID(ticket.number);
  }
}// namespace

PaymentServiceImpl::PaymentServiceImpl(PriceCalculator::Interface &priceCalculator,
  AccountService::Interface &accountService)
  : _priceCalculator(priceCalculator), _accountService(accountService)
{}

Cmn::Result<Domain::PaymentTicketID> PaymentServiceImpl::registerNewReservation(const Domain::ReservationTicket &ticket)
{
  auto ticketId = generateTicketID(ticket);
  assert(!needPay(ticketId).getResult());// TODO: Remove after completion work on error handling
  _tickets.insert(ticketId);
  return ticketId;
}
Cmn::Result<bool> PaymentServiceImpl::needPay(const Domain::PaymentTicketID &ticketID) const
{
  return _tickets.contains(ticketID);
}

Cmn::Result<void> PaymentServiceImpl::pay(const Domain::PaymentTicketID &ticketID)
{
  assert(needPay(ticketID).getResult());// TODO: Remove after completion work on error handling
  _tickets.erase(ticketID);
  return {};
}

Cmn::Result<Domain::PaymentTicket> PaymentServiceImpl::getPayment(const Domain::ExitRequest &req) const
{
  auto paymentTicketID = generateTicketID(req.vehicleNumber);
  if (const auto iter = _unpdaidTickets.find(paymentTicketID); iter != _unpdaidTickets.end())
  {
    return iter->second;
  }

  auto parkingReservation = _accountService.getParkingReservation(req.vehicleNumber);
  if (auto *err = parkingReservation.getError(); err != nullptr)
  {
    return CMN_NESTED_ERR(Errc::AccountServiceError, err);
  }

  const auto &parkingReservationRes = parkingReservation.getResult();

  const auto departureTime = req.time;
  auto price = _priceCalculator.calculateParkingPrice(parkingReservationRes, departureTime);

  if (auto *err = price.getError(); err != nullptr)
  {
    return CMN_NESTED_ERR(Errc::PriceCalculatorError, err);
  }

  Domain::PaymentTicket result;
  result.ID = std::move(paymentTicketID);
  result.parkingPrice = price.getResult();

  return result;
}

};// namespace Vertaler::ParkingSystem::BL::PaymentService