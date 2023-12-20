#include "Clock.h"
#include "Domain/Time.h"
#include "Factory.h"
#include <chrono>

namespace Vertaler::ParkingSystem::Hardware
{

namespace
{
}

class ClockImpl : public Clock
{
public:
  [[nodiscard]] Cmn::Result<Domain::TimePoint> now() const override
  {
    using namespace std::chrono;

    constexpr auto TimeRate = 240;// Map real time minute to 4hours in the system

    const auto ellapsedTime = std::chrono::system_clock::now() - _initialTime;
    const auto res = Domain::TimePoint{} + duration_cast<seconds>(ellapsedTime) * TimeRate;
    return res;
  }

private:
  Domain::TimePoint _initialTime{ std::chrono::system_clock::now() };
};

std::unique_ptr<Clock> createClock()
{
  return std::make_unique<ClockImpl>();
}

}// namespace Vertaler::ParkingSystem::Hardware