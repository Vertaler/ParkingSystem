#pragma once

#include "BarrierControllerBase.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class InputBarrierController final : public BarrierControllerBase
{
protected:
  // Handle ticket as ReservationRequest
  Cmn::Result<bool> shouldPassCar() override;
  Cmn::Result<bool> preparePrintingInfo() override;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController