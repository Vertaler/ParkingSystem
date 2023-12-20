#include "BarrierControllerBase.h"

#include "Domain/Vehicle.h"

#include "Hardware/Barrier/Barrier.h"
#include "Hardware/Clock/Clock.h"
#include "Hardware/Printer/Printer.h"
#include "Hardware/Scanner/Scanner.h"

#include <cstddef>
#include <ctime>

namespace Vertaler::ParkingSystem::BL::BarrierController
{

Cmn::Result<void> BarrierControllerBase::handleVehicle() const
{
  const auto &hardware = getHardwareFacade();
  const auto scannedData = hardware.getScanner().scan();
  // TODO Implement more complex logic of scanner result parsing
  // And move it to separate place
  const Domain::VehicleNumber vehicleNumber{ scannedData.getResult().data };

  const auto currentTime = hardware.getClock().now().getResult();
  const auto passRes = tryPassVehicle(vehicleNumber, currentTime);
  const auto &[shouldPassVehicle, printingInfo] = passRes.getResult();
  if (shouldPassVehicle)
  {
    hardware.getBarrier().passVehicle();
  }

  hardware.getPrinter().print(printingInfo);

  return {};
}

}// namespace Vertaler::ParkingSystem::BL::BarrierController