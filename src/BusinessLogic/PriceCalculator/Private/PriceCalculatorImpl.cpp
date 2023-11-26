#include "PriceCalculatorImpl.h"
#include "Domain/Money.h"
#include <chrono>

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

namespace
{
  constexpr size_t PricePerSecond = 10;
}

Cmn::Result<Domain::Money> PriceCalculatorImpl::calculateParkingPrice(const Domain::ReservationTicket &ticket,
  const Domain::TimePoint &departureTime) const
{
  const auto &arrivalTime = ticket.arrivalTime;
  const auto parkingDuration = (departureTime - arrivalTime);

  using namespace std::chrono;
  const auto parkingDurationSecs = duration_cast<seconds>(parkingDuration).count();

  Domain::Money parkingPrice{ parkingDurationSecs * PricePerSecond };
  return parkingPrice;
}

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator