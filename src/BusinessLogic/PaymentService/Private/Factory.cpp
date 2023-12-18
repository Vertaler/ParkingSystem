#include "BusinessLogic/PaymentService/Public/Factory.h"

#include "PaymentServiceImpl.h"

#include <memory>


namespace Vertaler::ParkingSystem::BL::PaymentService
{
std::unique_ptr<Interface> create(PriceCalculator::Interface &priceCalculator,
  AccountService::Interface &accountService)
{
  return std::make_unique<PaymentServiceImpl>(priceCalculator, accountService);
}
}// namespace Vertaler::ParkingSystem::BL::PaymentService
