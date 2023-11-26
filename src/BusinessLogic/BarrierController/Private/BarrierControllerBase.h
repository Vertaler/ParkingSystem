#pragma once

#include "BusinessLogic/BarrierController/Public/Interface.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class BarrierControllerBase : public BarrierController::Interface
{
public:
  Cmn::Result<void> handleCar(const Domain::CarInfo &) const override;

protected:
  virtual Cmn::Result<bool> shouldPassCar() = 0;
  virtual Cmn::Result<bool> preparePrintingInfo() = 0;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController