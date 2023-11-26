#include "Barrier.h"
#include "Factory.h"


namespace Vertaler::ParkingSystem::Hardware
{

namespace
{

  class BarrierImpl : public Barrier
  {
  public:
    Cmn::Result<void> passCar() override
    {
      return {};
    }
  };

}// namespace

std::unique_ptr<Barrier> createBarrier()
{
  return std::make_unique<BarrierImpl>();
}

}// namespace Vertaler::ParkingSystem::Hardware