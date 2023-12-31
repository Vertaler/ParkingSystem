#include "BusinessLogic/AccountService/Public/Factory.h"
#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/BarrierController/Public/Factory.h"
#include "BusinessLogic/BarrierController/Public/Interface.h"
#include "BusinessLogic/PaymentService/Public/Factory.h"
#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Factory.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"


#include "Domain/PaymentTicket.h"
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

using BarrierControllers = std::vector<std::unique_ptr<BL::BarrierController::Interface>>;


void handleVehicle(const BarrierControllers &controllers, const std::string &barrierType)
{
  size_t barrierNumber{};
  if (!scn::prompt("Please prompt barrier number\n", "{}", barrierNumber))
  {
    return;
  }
  if (barrierNumber >= controllers.size())
  {
    std::cerr << "There are only " << controllers.size() << barrierType << " barriers" << std::endl;
    return;
  }

  const auto &controller = controllers.at(barrierNumber);

  std::cout << "Handling " << barrierType << " vehicle. Please prompt vehicle number" << std::endl;
  const auto res = controller->handleVehicle();
  if (const auto *err = res.getError(); err != nullptr)
  {
    std::cerr << "Some error on " << barrierType << " vehicle" << std::endl;
  }
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
  const auto paymentService = BL::PaymentService::create();
  const auto accountService = BL::AccountService::create(*priceCalculator, *paymentService);

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
    "Write IN  to emulate incoming vehicle,\n"
    "OUT  to emulate outgoing vehicle\n"
    "PAY to emulate payment.\n";
  std::string command{};
  while (scn::prompt(promptMessage, "{}", command))
  {
    if (command == "OUT")
    {
      handleVehicle(outputBarrierControllers, "output");
    } else if (command == "IN")
    {
      handleVehicle(inputBarrierControllers, "input");
    } else if (command == "PAY")
    {
      Domain::PaymentTicketID paymentTicketID;
      if (!scn::prompt("Please provide payment ticket ID\n", "{}", paymentTicketID))
      {
        continue;
      }
      const auto res = paymentService->pay(paymentTicketID);
      if (res.getError() == nullptr)
      {
        std::cout << "Successfully paid for ticket " << paymentTicketID << std::endl;
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