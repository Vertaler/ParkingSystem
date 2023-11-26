#pragma once

#include <memory>

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{
class Interface;
std::unique_ptr<Interface> create();
}// namespace Vertaler::ParkingSystem::BL::PriceCalculator
