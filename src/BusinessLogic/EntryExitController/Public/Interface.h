#pragma once

#include "Observer.h"

#include "Common/Result.h"

#include "Domain/EntryExit.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

class Interface
{
public:
  virtual ~Interface() = default;
  virtual Cmn::Result<Domain::EntryResponse> entry(const Domain::EntryRequest &req) = 0;
  virtual Cmn::Result<Domain::ExitResponse> exit(const Domain::ExitRequest &req) = 0;
  virtual void registerObserver(Observer &observer) = 0;
};

}// namespace Vertaler::ParkingSystem::BL::EntryExitController