#pragma once

#include "Common/Result.h"
#include "Domain/Time.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Clock
{
public:
  virtual ~Clock() = default;
  [[nodiscard]] virtual Cmn::Result<Domain::TimePoint> now() const = 0;
};

}// namespace Vertaler::ParkingSystem::Hardware