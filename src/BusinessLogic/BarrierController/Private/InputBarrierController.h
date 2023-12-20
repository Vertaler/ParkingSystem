#pragma once

#include "BarrierControllerBase.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class InputBarrierController final : public BarrierControllerBase
{
public:
  using BarrierControllerBase::BarrierControllerBase;

protected:
  [[nodiscard]] virtual Cmn::Result<PassVehicleResult> tryPassVehicle(const Domain::VehicleNumber &vehicleNumber,
    const Domain::TimePoint &time) const override;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController