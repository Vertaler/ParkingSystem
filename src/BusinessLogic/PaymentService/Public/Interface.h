#pragma once

#include "Common/Result.h"

#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/PaymentTicket.h"

namespace Vertaler::ParkingSystem::BL::PaymentService
{

class Interface
{
public:
  virtual ~Interface() = default;

  virtual Cmn::Result<Domain::PaymentTicketID> registerNewReservation(const Domain::ReservationTicket &ticket) = 0;
  virtual Cmn::Result<bool> needPay(const Domain::PaymentTicketID &ticketID) const = 0;
  virtual Cmn::Result<void> pay(const Domain::PaymentTicketID &ticketID) = 0;
};

}// namespace Vertaler::ParkingSystem::BL::PaymentService