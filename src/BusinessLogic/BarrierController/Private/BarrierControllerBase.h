#pragma once

#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/BarrierController/Public/Interface.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"
#include "Hardware/Facade.h"
#include "Hardware/Printer/Printer.h"

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class BarrierControllerBase : public BarrierController::Interface
{
public:
  BarrierControllerBase(Hardware::Facade &hardwareFacade, AccountService::Interface &accountService)
    : _hardwareFacade(hardwareFacade), _accountService(accountService)
  {}

  [[nodiscard]] Cmn::Result<void> handleVehicle() const override;

protected:
  using PassVehicleResult = std::pair<bool, Hardware::Printer::PrintingInfo>;

  [[nodiscard]] virtual Cmn::Result<PassVehicleResult> tryPassVehicle(const Domain::Vehicle &vehicle,
    const Domain::TimePoint &time) const = 0;

  [[nodiscard]] Hardware::Facade &getHardwareFacade() const noexcept
  {
    return _hardwareFacade;
  }

  [[nodiscard]] AccountService::Interface &getAccountService() const noexcept
  {
    return _accountService;
  }

private:
  Hardware::Facade &_hardwareFacade;
  AccountService::Interface &_accountService;
};

}// namespace Vertaler::ParkingSystem::BL::BarrierController