#pragma once

#include "Interface.h"

#include "BusinessLogic/EntryExitController/Public/Observer.h"

#include "Common/CompositeInterface.h"

namespace Vertaler::ParkingSystem::BL::AccountService
{
using InterfaceWithObserver = Cmn::CompositeInterface<Interface, EntryExitController::Observer>;
}