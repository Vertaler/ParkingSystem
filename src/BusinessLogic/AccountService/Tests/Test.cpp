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

  // fakeit::Mock<PriceCalculator::Interface> priceCalculatorMock;
  // fakeit::Mock<PaymentService::Interface> paymentServiceMock;

  // const std::unique_ptr<Interface> accountService = create(priceCalculatorMock.get(), paymentServiceMock.get());
  // const auto time = std::chrono::system_clock::now();
  // const Domain::VehicleNumber vehicleNumber{ "123" };

  // SECTION("Reserve parking space")
  // {
  //   const Domain::Vehicle vehicle{ vehicleNumber };
  //   const Domain::ReservationRequest request{ vehicle, time };

  //   using namespace std::string_literals;
  //   When(Method(paymentServiceMock, registerNewReservation)).Return("123"s);

  //   auto res = accountService->reserveParkingSpace(request);

  //   REQUIRE(res.getError() == nullptr);
  //   REQUIRE(res.getResult().number == vehicleNumber);
  //   Verify(Method(paymentServiceMock, registerNewReservation));
  //   SECTION("Release after reserve. Payment required")
  //   {
  //     constexpr size_t MockedPrice = 1234;
  //     const Domain::Money MockedMoney{ MockedPrice };
  //     When(Method(paymentServiceMock, needPay)).Return(true);
  //     When(Method(priceCalculatorMock, calculateParkingPrice)).Return(MockedMoney);


  //     const Domain::ReleasingRequest request{ vehicleNumber, time };
  //     auto res = accountService->releaseParkingSpace(request);
  //     const auto &paymentTicket = res.getResult().paymentTicket;

  //     REQUIRE(res.getError() == nullptr);
  //     REQUIRE(res.getResult().status == Domain::ReleasingStatus::PaymentRequired);
  //     REQUIRE(res.getResult().paymentTicket.has_value());
  //     // NOLINTBEGIN(bugprone-unchecked-optional-access) Checked line above)
  //     REQUIRE(paymentTicket->parkingPrice.amount == MockedPrice);
  //     // NOLINTEND(bugprone-unchecked-optional-access)
  //     Verify(Method(priceCalculatorMock, calculateParkingPrice));
  //   }
  //   SECTION("Release after reserve. No payment required")
  //   {
  //     When(Method(paymentServiceMock, needPay)).Return(false);

  //     const Domain::ReleasingRequest request{ vehicleNumber, time };
  //     auto res = accountService->releaseParkingSpace(request);

  //     REQUIRE(res.getError() == nullptr);
  //     REQUIRE(res.getResult().status == Domain::ReleasingStatus::OK);
  //   }
  // }
  // SECTION("Release without reserve causes error")
  // {
  //   When(Method(paymentServiceMock, needPay)).Return(false);

  //   const Domain::ReleasingRequest request{ vehicleNumber, time };
  //   auto res = accountService->releaseParkingSpace(request);
  //   const auto *err = res.getError();

  //   REQUIRE(err != nullptr);
  //   REQUIRE(err->is(AccountService::Errc::ReservationNotFound));
  // }
}

}// namespace Vertaler::ParkingSystem::BL::AccountService::Tests