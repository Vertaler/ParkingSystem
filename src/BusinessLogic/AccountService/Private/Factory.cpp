#include "BusinessLogic/AccountService/Public/Factory.h"

#include "BusinessLogic/AccountService/Private/AccountServiceImpl.h"

namespace Vertaler::ParkingSystem::BL::AccountService
{

std::unique_ptr<Interface> create(PriceCalculator::Interface &priceCalculator,
  PaymentService::Interface &paymentService)
{
  return std::make_unique<AccountServiceImpl>(priceCalculator, paymentService);
}

}// namespace Vertaler::ParkingSystem::BL::AccountService