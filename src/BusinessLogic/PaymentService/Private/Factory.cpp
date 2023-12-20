#include "BusinessLogic/PaymentService/Public/Factory.h"

#include "PaymentServiceImpl.h"
#include <memory>


namespace Vertaler::ParkingSystem::BL::PaymentService
{
std::unique_ptr<Interface> create()
{
  return std::make_unique<PaymentServiceImpl>();
}
}// namespace Vertaler::ParkingSystem::BL::PaymentService
