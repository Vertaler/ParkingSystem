#include "BusinessLogic/AccountService/Public/Factory.h"

#include "BusinessLogic/AccountService/Private/AccountServiceImpl.h"

#include "BusinessLogic/AccountService/Public/InterfaceWithObserver.h"
#include "BusinessLogic/EntryExitController/Public/Interface.h"

namespace Vertaler::ParkingSystem::BL::AccountService
{

std::unique_ptr<InterfaceWithObserver> create()
{
  return std::make_unique<AccountServiceImpl>();
}

}// namespace Vertaler::ParkingSystem::BL::AccountService