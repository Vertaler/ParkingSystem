#pragma once

#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/PaymentTicket.h"
#include "Domain/Vehicle.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

class AccountServiceImpl final : public Interface
{
public:
  explicit AccountServiceImpl(const PriceCalculator::Interface &priceCalculator,
    PaymentService::Interface &paymentService);

  Cmn::Result<Domain::ReservationTicket> reserveParkingSpace(const Domain::ReservationRequest &req) override;
  Cmn::Result<Domain::ReleasingResponse> releaseParkingSpace(const Domain::ReleasingRequest &req) override;

private:
  const PriceCalculator::Interface &_priceCalculator;
  PaymentService::Interface &_paymentService;

  std::unordered_map<Domain::VehicleNumber, Domain::ReservationTicket> _storage;
  std::unordered_map<Domain::VehicleNumber, Domain::PaymentTicketID> _paymentTicketsIDs;
};

}// namespace Vertaler::ParkingSystem::BL::AccountService