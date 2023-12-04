#include "PriceCalculatorImpl.h"

#include "Rates.h"

#include "Domain/Money.h"
#include <chrono>

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

namespace
{
  constexpr size_t PricePerSecond = 10;

  struct NightDayDuration
  {
    std::chrono::minutes nightDuration;
    std::chrono::minutes dayDuration;
  };

  // Calculate total duration of night and day time at specified
  // time range
  NightDayDuration splitNightDay(const Domain::TimePoint &first, const Domain::TimePoint &second)
  {
    using namespace std::chrono;

    NightDayDuration result{};

    constexpr auto MinutesAtDay = 24 * 60;
    constexpr auto DayStart = 4 * 60;// 4:00
    constexpr auto DayEnd = 20 * 60;// 20:00
    constexpr auto MinutesAtNight = DayStart + MinutesAtDay - DayEnd;
    const auto firstMinuteAtDay = duration_cast<minutes>(first.time_since_epoch()).count() % MinutesAtDay;
    const auto totalMinuteCount = duration_cast<minutes>(second - first).count();

    // TODO: Can be optimized:
    // Calculate day and night time for first day
    // Calculate day and night time for last day
    // Calculate count of days between first and last
    // total daytime = first daytime + last daytime + 16h * days between
    // total nightime = first nightime + last nighttime + 8h * days between
    for (auto minuteCounter = firstMinuteAtDay; minuteCounter < totalMinuteCount;)
    {
      auto minuteAtDay = minuteCounter % MinutesAtDay;

      const auto step = [&minuteCounter, &totalMinuteCount, &minuteAtDay](auto nextPeriodStart, minutes &destination) {
        const auto timeUntilNextPeriod = nextPeriodStart - minuteAtDay;
        const auto increment = std::min(timeUntilNextPeriod, totalMinuteCount - minuteCounter);
        destination += minutes(increment);
        minuteCounter += increment;
      };

      if ((minuteAtDay > DayStart && minuteAtDay < DayEnd))
      {
        step(DayEnd, result.dayDuration);
      } else if (minuteAtDay < DayStart)
      {
        step(DayStart, result.nightDuration);
      } else
      {
        step(MinutesAtNight, result.nightDuration);
      }
    }

    return result;
  }

}// namespace


Cmn::Result<Domain::Money> PriceCalculatorImpl::calculateParkingPrice(const Domain::ReservationTicket &ticket,
  const Domain::TimePoint &departureTime) const
{
  const auto &arrivalTime = ticket.arrivalTime;
  const auto nightDayDuration = splitNightDay(arrivalTime, departureTime);

  const auto parkingPrice =
    CalculateByBaseRate(nightDayDuration.dayDuration) + CalculateByNightRate(nightDayDuration.nightDuration);
  return parkingPrice;
}

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator