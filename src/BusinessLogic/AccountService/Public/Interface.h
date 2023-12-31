#pragma once

#include "Common/Result.h"

#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"

namespace Vertaler::ParkingSystem::BL::AccountService
{

class Interface
{
public:
  virtual ~Interface() = default;
  virtual Cmn::Result<Domain::ReservationTicket> reserveParkingSpace(const Domain::ReservationRequest &req) = 0;
  virtual Cmn::Result<Domain::ReleasingResponse> releaseParkingSpace(const Domain::ReleasingRequest &req) = 0;
};

}// namespace Vertaler::ParkingSystem::BL::AccountService