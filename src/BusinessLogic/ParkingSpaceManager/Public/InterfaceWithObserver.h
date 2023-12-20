#pragma once

#include "Interface.h"

#include "BusinessLogic/EntryExitController/Public/Observer.h"

#include "Common/CompositeInterface.h"

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{
using InterfaceWithObserver = Cmn::CompositeInterface<Interface, EntryExitController::Observer>;
}