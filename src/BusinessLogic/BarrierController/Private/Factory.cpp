#include "BusinessLogic/BarrierController/Public/Factory.h"

#include "InputBarrierController.h"
#include "OutputBarrierController.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

std::unique_ptr<Interface> createInputContoller(Hardware::Facade &hardware, AccountService::Interface &accountService)
{
  return std::make_unique<InputBarrierController>(hardware, accountService);
}

std::unique_ptr<Interface> createOutputContoller(Hardware::Facade &hardware, AccountService::Interface &accountService)
{
  return std::make_unique<OutputBarrierController>(hardware, accountService);
}


}// namespace Vertaler::ParkingSystem::BL::BarrierController