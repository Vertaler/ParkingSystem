
#include "Rates.h"

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

namespace
{
  constexpr auto PricePerMinute = 2;
  constexpr auto NightPriceDiscount = 0.7;

}// namespace

Domain::Money CalculateByBaseRate(std::chrono::minutes parkingDuration)
{
  return Domain::Money{ static_cast<size_t>(parkingDuration.count() * PricePerMinute) };
}

Domain::Money CalculateByNightRate(std::chrono::minutes parkingDuration)
{
  return NightPriceDiscount * CalculateByBaseRate(parkingDuration);
}

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator