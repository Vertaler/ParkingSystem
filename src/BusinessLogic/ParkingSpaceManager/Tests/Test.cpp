#include <catch2/catch_test_macros.hpp>

#include "BusinessLogic/ParkingSpaceManager/Public/Errors.h"
#include "BusinessLogic/ParkingSpaceManager/Public/Factory.h"
#include "BusinessLogic/ParkingSpaceManager/Public/Interface.h"
#include "Common/Result.h"
#include "Domain/Vehicle.h"

#include <memory>

namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager::Tests
{

TEST_CASE("Basic parking space manager tests", "[ParkingSpaceManager]")
{

  const std::unique_ptr<Interface> parkingSpaceManager = create();
  const Domain::VehicleNumber vehicleNumber{ "123" };

  SECTION("Reservation not found")
  {
    const auto res = parkingSpaceManager->getParkingReservation(vehicleNumber);

    const auto *err = res.getError();
    REQUIRE(err != nullptr);
    REQUIRE(err->is(Errc::ReservationNotFound));
  }
}

}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager::Tests