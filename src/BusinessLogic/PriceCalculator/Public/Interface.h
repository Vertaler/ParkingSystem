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
  virtual Cmn::Result<Domain::Money> calculateParkingPrice(const Domain::ReleasingRequest &req) const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator