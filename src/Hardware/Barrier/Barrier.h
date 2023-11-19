#pragma once

#include "Common/Result.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Barrier
{
public:
  virtual ~Barrier() = default;
  // open/or close
  virtual Result<void> toggle() = 0;
  virtual Result<bool> isOpen() const = 0;
}

}// namespace Vertaler::ParkingSystem::Hardware