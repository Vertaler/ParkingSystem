#pragma once

#include "BusinessLogic/PriceCalculator/Public/Interface.h"

namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

class PriceCalculatorImpl : public Interface
{
public:
  Cmn::Result<Domain::Money> calculateParkingPrice(const Domain::ReservationTicket &ticket,
    const Domain::TimePoint &departureTime) const override;
};

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator