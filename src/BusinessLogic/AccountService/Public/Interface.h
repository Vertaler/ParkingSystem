#pragma once

#include "Common/Result.h"

#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/PaymentTicket.h"

namespace Vertaler::ParkingSystem::BL::AccountService
{

class Interface
{
public:
  virtual ~Interface() = default;
  Cmn::Result<Domain::ReservationTicket> reserveParkingSpace(const Domain::ReservationRequest &req);
  Cmn::Result<Domain::PaymentTicket> releaseParkingSpace(const Domain::ReleasingRequest &req);

}// namespace Vertaler::ParkingSystem::BL::AccountService