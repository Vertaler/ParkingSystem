#pragma once

#include "BarrierControllerBase.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class InputBarrierController : public BarrierControllerBase
{
protected:
  // Handle ticket as ReservationRequest
  Cmn::Result<void> handleScaningResult() override;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController