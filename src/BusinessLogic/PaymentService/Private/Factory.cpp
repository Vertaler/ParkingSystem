#include "BusinessLogic/PaymentService/Public/Factory.h"

#include "PaymentServiceImpl.h"

#include <memory>


namespace Vertaler::ParkingSystem::BL::PaymentService
{
std::unique_ptr<Interface> create(PriceCalculator::Interface &priceCalculator,
  ParkingSpaceManager::Interface &parkingSpaceManager)
{
  return std::make_unique<PaymentServiceImpl>(priceCalculator, parkingSpaceManager);
}
}// namespace Vertaler::ParkingSystem::BL::PaymentService
