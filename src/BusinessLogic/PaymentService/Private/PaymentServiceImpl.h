#pragma once

#pragma once

#include "BusinessLogic/PaymentService/Public/Interface.h"

#include <unordered_set>

namespace Vertaler::ParkingSystem::BL::PaymentService
{

class PaymentServiceImpl : public Interface
{
public:
  Cmn::Result<Domain::PaymentTicketID> registerNewReservation(const Domain::ReservationTicket &ticket) override;
  Cmn::Result<bool> needPay(const Domain::PaymentTicketID &ticketID) const override;
  Cmn::Result<void> pay(const Domain::PaymentTicketID &ticketID) override;

private:
  std::unordered_set<Domain::PaymentTicketID> _tickets;
};

}// namespace Vertaler::ParkingSystem::BL::PaymentService