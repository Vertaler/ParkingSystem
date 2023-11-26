#pragma once

#include "Common/Result.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Barrier
{
public:
  virtual ~Barrier() = default;
  // open, wait until car passed and close
  virtual Cmn::Result<void> passCar() = 0;
};

}// namespace Vertaler::ParkingSystem::Hardware