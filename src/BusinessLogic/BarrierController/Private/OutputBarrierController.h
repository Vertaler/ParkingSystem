#pragma once

#include "BarrierControllerBase.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class OutputBarrierController final : public BarrierControllerBase
{
protected:
  // Handle ticket as ReservationTicket
  Cmn::Result<bool> shouldPassCar() override;
  Cmn::Result<bool> preparePrintingInfo() override;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController