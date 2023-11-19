#pragma once

#include "Common/Result.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Sensor
{
public:
  virtual ~Sensor() = default;
  virtual waitCarPassed() const = 0
};

}// namespace Vertaler::ParkingSystem::Hardware