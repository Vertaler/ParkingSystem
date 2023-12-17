#include "EntryExitControllerImpl.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

Cmn::Result<Domain::EntryResponse> EntryExitControllerImpl::entry(const Domain::EntryRequest & /*req*/)
{
  return {};
}

Cmn::Result<Domain::ExitResponse> EntryExitControllerImpl::exit(const Domain::ExitRequest & /*req*/)
{
  return {};
}

void EntryExitControllerImpl::registerObserver(Observer & /*observer*/) {}

}// namespace Vertaler::ParkingSystem::BL::EntryExitController