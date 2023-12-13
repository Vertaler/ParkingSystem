#pragma once

#include <memory>

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{
class Interface;
}

namespace Vertaler::ParkingSystem::BL::PaymentService
{
class Interface;
}

namespace Vertaler::ParkingSystem::BL::AccountService
{
class Interface;
std::unique_ptr<Interface> create(PriceCalculator::Interface &priceCalculator,
  PaymentService::Interface &paymentService);

}// namespace Vertaler::ParkingSystem::BL::AccountService