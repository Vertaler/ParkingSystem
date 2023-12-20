#pragma once

#include "Observer.h"

#include "Common/CompositeInterface.h"
#include "Common/Result.h"

#include "Domain/EntryExit.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

class Observable
{
public:
  virtual ~Observable() = default;

  virtual void registerObserver(Observer &observer) = 0;
};

class EntryExitHandler
{
public:
  virtual ~EntryExitHandler() = default;

  virtual Cmn::Result<Domain::EntryResponse> entry(const Domain::EntryRequest &req) = 0;
  virtual Cmn::Result<Domain::ExitResponse> exit(const Domain::ExitRequest &req) = 0;
};

using Interface = Cmn::CompositeInterface<Observable, EntryExitHandler>;

}// namespace Vertaler::ParkingSystem::BL::EntryExitController