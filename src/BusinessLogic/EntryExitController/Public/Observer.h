#pragma once

#include "Domain/EntryExit.h"

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
class Observer
{
public:
  virtual ~Observer() = default;

  virtual void onEntry(const Domain::EntryRequest &req) = 0;
  virtual void onExit(const Domain::ExitRequest &req) = 0;
};
}// namespace Vertaler::ParkingSystem::BL::EntryExitController