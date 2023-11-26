#include "Clock.h"
#include "Factory.h"

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
    return Cmn::Result<Domain::TimePoint>{ std::chrono::system_clock::now() };
  }
};

std::unique_ptr<Clock> createClock()
{
  return std::make_unique<ClockImpl>();
}

}// namespace Vertaler::ParkingSystem::Hardware