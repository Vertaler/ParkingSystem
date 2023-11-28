#include <catch2/catch_test_macros.hpp>

#include "BusinessLogic/PriceCalculator/Public/Factory.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Time.h"

#include <chrono>

namespace Vertaler::ParkingSystem::BL::PriceCalculator::Tests
{

TEST_CASE("Price calculated w/o errors", "[PriceCalculator]")
{
  auto priceCalculator = create();

  using namespace std::chrono;
  using namespace std::chrono_literals;

  const auto arrivalTime = system_clock::now();
  const auto departureTime = arrivalTime + 10s;
  Domain::ReservationTicket ticket{ Domain::VehicleNumber{ "123" }, arrivalTime };
  auto res = priceCalculator->calculateParkingPrice(ticket, departureTime);

  REQUIRE(res.getError() == nullptr);
  REQUIRE(res.getResult().amount == 100);
}

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator::Tests