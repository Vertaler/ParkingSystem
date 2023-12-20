#pragma once

#include "BusinessLogic/BarrierController/Public/Interface.h"
#include "BusinessLogic/EntryExitController/Public/Interface.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"
#include "Hardware/Facade.h"
#include "Hardware/Printer/Printer.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class BarrierControllerBase : public BarrierController::Interface
{
public:
  BarrierControllerBase(Hardware::Facade &hardwareFacade, EntryExitController::EntryExitHandler &entryExitHandler)
    : _hardwareFacade(hardwareFacade), _entryExitHandler(entryExitHandler)
  {}

  [[nodiscard]] Cmn::Result<void> handleVehicle() const override;

protected:
  using PassVehicleResult = std::pair<bool, Hardware::Printer::PrintingInfo>;

  [[nodiscard]] virtual Cmn::Result<PassVehicleResult> tryPassVehicle(const Domain::VehicleNumber &vehicle,
    const Domain::TimePoint &time) const = 0;

  [[nodiscard]] Hardware::Facade &getHardwareFacade() const noexcept
  {
    return _hardwareFacade;
  }

  [[nodiscard]] EntryExitController::EntryExitHandler &getEntryExitHandler() const noexcept
  {
    return _entryExitHandler;
  }

private:
  Hardware::Facade &_hardwareFacade;
  EntryExitController::EntryExitHandler &_entryExitHandler;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController