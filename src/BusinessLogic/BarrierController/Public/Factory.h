#pragma once

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

std::unique_ptr<Interface> createInputContoller(Hardware::Facade &hardware,
  EntryExitController::EntryExitHandler &entryExitHandler);
std::unique_ptr<Interface> createOutputContoller(Hardware::Facade &hardware,
  EntryExitController::EntryExitHandler &entryExitHandler);

}// namespace Vertaler::ParkingSystem::BL::BarrierController