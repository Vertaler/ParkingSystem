#pragma once

#include "BarrierControllerBase.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class OutputBarrierController : public BarrierControllerBase
{
protected:
  // Handle ticket as ReservationTicket
  Cmn::Result<void> handleScaningResult() override;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController