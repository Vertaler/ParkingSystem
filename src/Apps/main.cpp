#include "BusinessLogic/AccountService/Public/Factory.h"
#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/BarrierController/Public/Factory.h"
#include "BusinessLogic/BarrierController/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Factory.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"

#include "Hardware/Facade.h"

#include "Hardware/Barrier/Barrier.h"
#include "Hardware/Clock/Clock.h"
#include "Hardware/Printer/Printer.h"
#include "Hardware/Scanner/Scanner.h"


#include <cstdlib>
#include <iostream>
#include <string>

using namespace Vertaler;
using namespace Vertaler::ParkingSystem;

bool readLine(std::string &line)
{
  std::cout << "Write IN <emulate incoming vehicle> or OUT <emulate outgoing vehicle>" << std::endl;
  return !!std::getline(std::cin, line);
}

int main(int /*argc*/, const char ** /*argv*/)
try
{
  const auto hardware = Hardware::createFacade(std::cout, std::cin);
  const auto priceCalculator = BL::PriceCalculator::create();
  const auto accountService = BL::AccountService::create(*priceCalculator);
  const auto inputBarrierController = BL::BarrierController::createInputContoller(*hardware, *accountService);
  const auto outputBarrierController = BL::BarrierController::createOutputContoller(*hardware, *accountService);

  std::string command{};
  while (readLine(command))
  {
    if (command == "OUT")
    {
      std::cout << "Handling outgoing vehicle. Please prompt vehicle number" << std::endl;
      const auto res = outputBarrierController->handleVehicle();
      if (const auto *err = res.getError(); err != nullptr)
      {
        std::cerr << "Some error on outgoing vehicle" << std::endl;
      }
    } else if (command == "IN")
    {
      std::cout << "Handling incoming vehicle. Please prompt vehicle number" << std::endl;
      const auto res = inputBarrierController->handleVehicle();
      if (const auto *err = res.getError(); err != nullptr)
      {
        std::cerr << "Some error on incoming vehicle" << std::endl;
      }
    } else
    {
      std::cerr << "Unknown command " << command << std::endl;
    }
  }

  return EXIT_SUCCESS;
} catch (const std::exception &exc)
{
  std::cerr << "Exception thrown: " << exc.what() << std::endl;
  return EXIT_FAILURE;
}