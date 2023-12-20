#include "BusinessLogic/BarrierController/Public/Factory.h"

#include "InputBarrierController.h"
#include "OutputBarrierController.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

std::unique_ptr<Interface> createInputContoller(Hardware::Facade &hardware,
  EntryExitController::EntryExitHandler &entryExitHandler)
{
  return std::make_unique<InputBarrierController>(hardware, entryExitHandler);
}

std::unique_ptr<Interface> createOutputContoller(Hardware::Facade &hardware,
  EntryExitController::EntryExitHandler &entryExitHandler)
{
  return std::make_unique<OutputBarrierController>(hardware, entryExitHandler);
}


}// namespace Vertaler::ParkingSystem::BL::BarrierController