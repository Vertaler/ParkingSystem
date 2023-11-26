#include "BusinessLogic/AccountService/Public/Factory.h"

#include "BusinessLogic/AccountService/Private/AccountServiceImpl.h"

namespace Vertaler::ParkingSystem::BL::AccountService
{

std::unique_ptr<Interface> create(PriceCalculator::Interface &priceCalculator)
{
  return std::make_unique<AccountServiceImpl>(priceCalculator);
}

}// namespace Vertaler::ParkingSystem::BL::AccountService