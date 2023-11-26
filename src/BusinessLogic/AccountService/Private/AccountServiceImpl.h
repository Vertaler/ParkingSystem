#pragma once

#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

class AccountServiceImpl final : public Interface
{
public:
  explicit AccountServiceImpl(const PriceCalculator::Interface &priceCalculator);

  Cmn::Result<Domain::ReservationTicket> reserveParkingSpace(const Domain::ReservationRequest &req) override;
  Cmn::Result<Domain::PaymentTicket> releaseParkingSpace(const Domain::ReleasingRequest &req) override;

private:
  const PriceCalculator::Interface &_priceCalculator;

  std::unordered_map<std::string, Domain::ReservationTicket> _storage;
};

}// namespace Vertaler::ParkingSystem::BL::AccountService