#pragma once

#include "BusinessLogic/AccountService/Public/InterfaceWithObserver.h"

#include <memory>

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
class Observable;
}

namespace Vertaler::ParkingSystem::BL::AccountService
{
std::unique_ptr<InterfaceWithObserver> create();
}// namespace Vertaler::ParkingSystem::BL::AccountService