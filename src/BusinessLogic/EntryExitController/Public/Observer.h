#pragma once

namespace Vertaler::ParkingSystem::BL::EntryExitController
{
class Observer
{
public:
  virtual ~Observer() = default;

  virtual void onEntry() noexcept;
  virtual void onExit() noexcept;
};
}// namespace Vertaler::ParkingSystem::BL::EntryExitController