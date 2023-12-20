#include "BusinessLogic/PriceCalculator/Public/Factory.h"

#include "PriceCalculatorImpl.h"

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{
std::unique_ptr<Interface> create()
{
  return std::make_unique<PriceCalculatorImpl>();
}
}// namespace Vertaler::ParkingSystem::BL::PriceCalculator
