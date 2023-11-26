#pragma once

#include <memory>

namespace Vertaler::ParkingSystem::Hardware
{

class Clock;
std::unique_ptr<Clock> createClock();

}// namespace Vertaler::ParkingSystem::Hardware