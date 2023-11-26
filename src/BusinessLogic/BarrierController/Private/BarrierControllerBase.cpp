#include "BarrierControllerBase.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

Cmn::Result<void> BarrierControllerBase::handleCar(const Domain::CarInfo & /*unused*/) const
{
  return {};
}

}// namespace Vertaler::ParkingSystem::BL::BarrierController