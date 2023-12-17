#pragma once

#include "BusinessLogic/EntryExitController/Public/Interface.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

class EntryExitControllerImpl : public Interface
{
public:
  Cmn::Result<Domain::EntryResponse> entry(const Domain::EntryRequest &req) override;
  Cmn::Result<Domain::ExitResponse> exit(const Domain::ExitRequest &req) override;
  virtual void registerObserver(Observer &observer) override;
};

}// namespace Vertaler::ParkingSystem::BL::EntryExitController