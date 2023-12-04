#pragma once

#include "Domain/Money.h"

#include <chrono>

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

Domain::Money CalculateByBaseRate(std::chrono::minutes parkingDuration);
Domain::Money CalculateByNightRate(std::chrono::minutes parkingDuration);

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator