#include "BusinessLogic/ParkingSpaceManager/Public/Factory.h"

#include "BusinessLogic/ParkingSpaceManager/Private/ParkingSpaceManagerImpl.h"

#include "BusinessLogic/EntryExitController/Public/Interface.h"
#include "BusinessLogic/ParkingSpaceManager/Public/InterfaceWithObserver.h"

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{

std::unique_ptr<InterfaceWithObserver> create()
{
  return std::make_unique<ParkingSpaceManagerImpl>();
}

}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager