#pragma once

#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include <memory>

namespace Vertaler::ParkingSystem::BL
{

namespace PriceCalculator
{
  class Interface;
}

namespace ParkingSpaceManager
{
  class Interface;
}

}// namespace Vertaler::ParkingSystem::BL

namespace Vertaler::ParkingSystem::BL::PaymentService
{
class Interface;
std::unique_ptr<Interface> create(PriceCalculator::Interface &priceCalculator,
  ParkingSpaceManager::Interface &parkingSpaceManager);
}// namespace Vertaler::ParkingSystem::BL::PaymentService
