#pragma once

#include "Common/Result.h"

#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class Interface
{
public:
  virtual ~Interface() = default;
  [[nodiscard]] virtual Cmn::Result<void> handleVehicle() const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController