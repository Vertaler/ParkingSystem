#pragma once

#include "Common/Result.h"

#include "Domain/EntryExit.h"
#include "Domain/ParkingReservation.h"
#include "Domain/PaymentTicket.h"
#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::PaymentService
{

class Interface
{
public:
  virtual ~Interface() = default;

  virtual Cmn::Result<Domain::PaymentTicketID> registerNewReservation(const Domain::ReservationTicket &ticket) = 0;
  [[nodiscard]] virtual Cmn::Result<bool> needPay(const Domain::PaymentTicketID &ticketID) const = 0;
  virtual Cmn::Result<void> pay(const Domain::PaymentTicketID &ticketID) = 0;
  [[nodiscard]] virtual Cmn::Result<Domain::PaymentTicketOpt> getPayment(const Domain::ExitRequest &req) const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::PaymentService