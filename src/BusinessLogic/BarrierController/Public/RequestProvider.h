#pragma once

#include "Common/Result.h"

#include "Domain/Vehicle.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class RequestProvider
{
public:
  virtual ~RequestProvider() = default;
  [[nodiscard]] virtual Cmn::Result<Domain::VehicleNumber> receiveVehicleNumber() const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController