#pragma once

#include "BusinessLogic/ParkingSpaceManager/Public/InterfaceWithObserver.h"

#include <memory>

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
class Observable;
}

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{
std::unique_ptr<InterfaceWithObserver> create();
}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager