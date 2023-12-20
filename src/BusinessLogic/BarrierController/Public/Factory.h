#pragma once

#include "BusinessLogic/BarrierController/Public/RequestProvider.h"
#include "BusinessLogic/EntryExitController/Public/Interface.h"
#include <memory>

namespace Vertaler::ParkingSystem::Hardware
{
class Facade;
}

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
class EntryExitHandler;
}

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class Interface;
class RequestProvider;

std::unique_ptr<Interface> createInputContoller(Hardware::Facade &hardware,
  EntryExitController::EntryExitHandler &entryExitHandler,
  const RequestProvider &requestProvider);
std::unique_ptr<Interface> createOutputContoller(Hardware::Facade &hardware,
  EntryExitController::EntryExitHandler &entryExitHandler,
  const RequestProvider &requestProvider);

}// namespace Vertaler::ParkingSystem::BL::BarrierController