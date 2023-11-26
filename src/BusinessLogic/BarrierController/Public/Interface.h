#pragma once

#include "Common/Result.h"

#include "Domain/CarInfo.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class Interface
{
public:
  virtual ~Interface() = default;
  virtual Cmn::Result<void> handleCar(const Domain::CarInfo &) const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController