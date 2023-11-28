#include <catch2/catch_test_macros.hpp>

#include "BusinessLogic/AccountService/Public/Factory.h"
#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include "Common/Result.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Time.h"
#include "Domain/Vehicle.h"

#include <chrono>

namespace Vertaler::ParkingSystem::BL::AccountService::Tests
{

namespace
{
  class PriceCalculatorMock : public PriceCalculator::Interface
  {
  public:
    explicit PriceCalculatorMock(size_t result) : _result({ result }) {}

    Cmn::Result<Domain::Money> calculateParkingPrice(const Domain::ReservationTicket & /*ticket*/,
      const Domain::TimePoint & /*departureTime*/) const override
    {
      _callCount++;
      return _result;
    }

    size_t callCount() const noexcept
    {
      return _callCount;
    }

  private:
    mutable size_t _callCount{ 0 };
    Domain::Money _result;
  };
}// namespace

TEST_CASE("Basic account service tests", "[AccountService]")
{
  constexpr size_t MockedPrice = 1234;

  PriceCalculatorMock priceCalculatorMock(MockedPrice);
  PriceCalculator::Interface &priceCalculator = priceCalculatorMock;
  std::unique_ptr<Interface> accountService = create(priceCalculatorMock);

  using namespace std::chrono;
  using namespace std::chrono_literals;

  const auto time = system_clock::now();
  const Domain::VehicleNumber vehicleNumber{ "123" };

  {
    const Domain::Vehicle vehicle{ vehicleNumber };
    Domain::ReservationRequest request{ vehicle, time };
    auto res = accountService->reserveParkingSpace(request);
    REQUIRE(res.getError() == nullptr);
    REQUIRE(res.getResult().number.asString() == vehicleNumber.asString());
  }

  {
    Domain::ReleasingRequest request{ vehicleNumber, time };
    auto res = accountService->releaseParkingSpace(request);
    REQUIRE(res.getError() == nullptr);
    REQUIRE(res.getResult().parkingPrice.amount == MockedPrice);
    REQUIRE(priceCalculatorMock.callCount() == 1);
  }
}

}// namespace Vertaler::ParkingSystem::BL::AccountService::Tests