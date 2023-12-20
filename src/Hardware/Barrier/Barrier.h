#pragma once

#include "Common/Result.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Barrier
{
public:
  virtual ~Barrier() = default;
  // open, wait until vehicle passed and close
  virtual Cmn::Result<void> passVehicle() = 0;
};

}// namespace Vertaler::ParkingSystem::Hardware