#pragma once

#include "Common/Result.h"

#include "Domain/Money.h"
#include "Domain/ParkingReleasing.h"


namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

class Interface
{
public:
  virtual ~Interface() = default;
  Cmn::Result<Money> calculateParkinPrice(const Domain::ReleasingRequest &req) const = 0;
}

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator