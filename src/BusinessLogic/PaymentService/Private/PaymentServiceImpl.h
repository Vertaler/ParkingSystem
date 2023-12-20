#pragma once

#include "BusinessLogic/ParkingSpaceManager/Public/Interface.h"
#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"

#include "Domain/PaymentTicket.h"
#include "Domain/Vehicle.h"

#include <unordered_map>
#include <unordered_set>

namespace Vertaler::ParkingSystem::BL::PaymentService
{

class PaymentServiceImpl : public Interface
{
public:
  PaymentServiceImpl(PriceCalculator::Interface &priceCalculator, ParkingSpaceManager::Interface &parkingSpaceManager);

  Cmn::Result<Domain::PaymentTicketID> registerNewReservation(const Domain::ReservationTicket &ticket) override;
  Cmn::Result<bool> needPay(const Domain::PaymentTicketID &ticketID) const override;
  Cmn::Result<void> pay(const Domain::PaymentTicketID &ticketID) override;
  Cmn::Result<Domain::PaymentTicketOpt> getPayment(const Domain::ExitRequest &req) const override;

private:
  std::unordered_set<Domain::PaymentTicketID> _tickets;
  std::unordered_map<Domain::PaymentTicketID, Domain::PaymentTicket> _unpdaidTickets;

  ParkingSpaceManager::Interface &_parkingSpaceManager;
  PriceCalculator::Interface &_priceCalculator;
};

}// namespace Vertaler::ParkingSystem::BL::PaymentService