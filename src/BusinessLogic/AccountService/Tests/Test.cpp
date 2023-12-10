#include <catch2/catch_test_macros.hpp>

#include "BusinessLogic/AccountService/Public/Factory.h"
#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include "Common/Result.h"
#include "Domain/Money.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

#include <chrono>
#include <climits>
#include <fakeit.hpp>

namespace Vertaler::ParkingSystem::BL::AccountService::Tests
{

using namespace fakeit;

TEST_CASE("Basic account service tests", "[AccountService]")
{

  fakeit::Mock<PriceCalculator::Interface> priceCalculatorMock;
  fakeit::Mock<PaymentService::Interface> paymentServiceMock;

  std::unique_ptr<Interface> accountService = create(priceCalculatorMock.get(), paymentServiceMock.get());
  const auto time = std::chrono::system_clock::now();
  const Domain::VehicleNumber vehicleNumber{ "123" };

  {
    const Domain::Vehicle vehicle{ vehicleNumber };
    Domain::ReservationRequest request{ vehicle, time };

    auto res = accountService->reserveParkingSpace(request);

    REQUIRE(res.getError() == nullptr);
    REQUIRE(res.getResult().number == vehicleNumber);
    Verify(Method(paymentServiceMock, registerNewReservation));
  }

  {
    constexpr size_t MockedPrice = 1234;
    const Domain::Money MockedMoney{ MockedPrice };
    When(Method(paymentServiceMock, needPay)).Return(true);
    When(Method(priceCalculatorMock, calculateParkingPrice)).Return(MockedMoney);


    Domain::ReleasingRequest request{ vehicleNumber, time };
    auto res = accountService->releaseParkingSpace(request);
    const auto &paymentTicket = res.getResult().paymentTicket;

    REQUIRE(res.getError() == nullptr);
    REQUIRE(res.getResult().status == Domain::ReleasingStatus::PaymentRequired);
    REQUIRE(paymentTicket->parkingPrice.amount == MockedPrice);
    Verify(Method(priceCalculatorMock, calculateParkingPrice));
  }
  {
    When(Method(paymentServiceMock, needPay)).Return(false);

    Domain::ReleasingRequest request{ vehicleNumber, time };
    auto res = accountService->releaseParkingSpace(request);

    REQUIRE(res.getError() == nullptr);
    REQUIRE(res.getResult().status == Domain::ReleasingStatus::OK);
  }
}

}// namespace Vertaler::ParkingSystem::BL::AccountService::Tests