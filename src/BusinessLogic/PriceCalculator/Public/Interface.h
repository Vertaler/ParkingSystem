#pragma once

#include "Common/Result.h"

#include "Domain/Money.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/Time.h"


namespace Vertaler::ParkingSystem::BL::PriceCalculator
{

class Interface
{
public:
  virtual ~Interface() = default;
  virtual Cmn::Result<Domain::Money> calculateParkingPrice(const Domain::ReservationTicket &ticket,
    const Domain::TimePoint &departureTime) const = 0;
};

}// namespace Vertaler::ParkingSystem::BL::PriceCalculator