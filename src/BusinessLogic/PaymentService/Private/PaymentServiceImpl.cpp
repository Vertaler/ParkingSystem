#include "PaymentServiceImpl.h"

namespace Vertaler::ParkingSystem::BL::PaymentService
{

Cmn::Result<Domain::PaymentTicketID> PaymentServiceImpl::registerNewReservation(const Domain::ReservationTicket &ticket)
{
  auto ticketId = ticket.number.asString();
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

};// namespace Vertaler::ParkingSystem::BL::PaymentService