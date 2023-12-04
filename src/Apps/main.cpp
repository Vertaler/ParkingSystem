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


#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <scn/scn.h>

using namespace Vertaler;
using namespace Vertaler::ParkingSystem;

bool readLine(std::string &line)
{
  std::cout << "Write IN <number of input barrier> to emulate incoming vehicle  or OUT  <number of output barrier> to "
               "emulate outgoing vehicle"
            << std::endl;
  return !!std::getline(std::cin, line);
}

int main(int argc, const char **argv)
try
{
  if (argc < 3)
  {
    std::cout << "Usage: ParkingSystem <input barriers count> <output barriers count>" << std::endl;
    return EXIT_SUCCESS;
  }

  // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  const auto inputBarriersCount = std::stoi(argv[1]);
  const auto outputBarriersCount = std::stoi(argv[2]);
  // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

  const auto hardware = Hardware::createFacade(std::cout, std::cin);
  const auto priceCalculator = BL::PriceCalculator::create();
  const auto accountService = BL::AccountService::create(*priceCalculator);

  using BarrierControllers = std::vector<std::unique_ptr<BL::BarrierController::Interface>>;
  BarrierControllers inputBarrierControllers;
  BarrierControllers outputBarrierControllers;

  inputBarrierControllers.reserve(inputBarriersCount);
  for (size_t i = 0; i < inputBarriersCount; ++i)
  {
    inputBarrierControllers.push_back(BL::BarrierController::createInputContoller(*hardware, *accountService));
  }

  outputBarrierControllers.reserve(outputBarriersCount);
  for (size_t i = 0; i < outputBarriersCount; ++i)
  {
    outputBarrierControllers.push_back(BL::BarrierController::createOutputContoller(*hardware, *accountService));
  }

  const char *promptMessage =
    "Write IN <number of input barrier> to emulate incoming vehicle  or OUT  <number of output barrier> to emulate "
    "outgoing vehicle ";
  std::string command{};
  size_t barrierNumber{};
  while (scn::prompt(promptMessage, "{} {}", command, barrierNumber))
  {
    if (command == "OUT")
    {
      if (barrierNumber >= outputBarriersCount)
      {
        std::cerr << "There are only " << outputBarriersCount << " output barriers" << std::endl;
        continue;
      }

      std::cout << "Handling outgoing vehicle. Please prompt vehicle number" << std::endl;
      const auto res = outputBarrierControllers[barrierNumber]->handleVehicle();
      if (const auto *err = res.getError(); err != nullptr)
      {
        std::cerr << "Some error on outgoing vehicle" << std::endl;
      }
    } else if (command == "IN")
    {
      if (barrierNumber >= inputBarriersCount)
      {
        std::cerr << "There are only " << inputBarriersCount << " input barriers" << std::endl;
        continue;
      }

      std::cout << "Handling incoming vehicle. Please prompt vehicle number" << std::endl;
      const auto res = inputBarrierControllers[barrierNumber]->handleVehicle();
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