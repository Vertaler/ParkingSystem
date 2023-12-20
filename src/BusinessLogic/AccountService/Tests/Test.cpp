#include <catch2/catch_test_macros.hpp>

#include "BusinessLogic/AccountService/Public/Errors.h"
#include "BusinessLogic/AccountService/Public/Factory.h"
#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include "Common/Result.h"
#include "Domain/Money.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Vehicle.h"

#include <chrono>
#include <cstddef>
#include <memory>

#include <fakeit.hpp>

namespace Vertaler::ParkingSystem::BL::AccountService::Tests
{

using namespace fakeit;

TEST_CASE("Basic account service tests", "[AccountService]")
{

  const std::unique_ptr<Interface> accountService = create();
  const Domain::VehicleNumber vehicleNumber{ "123" };

  SECTION("Reservation not found")
  {
    const auto res = accountService->getParkingReservation(vehicleNumber);

    const auto *err = res.getError();
    REQUIRE(err != nullptr);
    REQUIRE(err->is(Errc::ReservationNotFound));
  }
}

}// namespace Vertaler::ParkingSystem::BL::AccountService::Tests