#pragma once

#include "BusinessLogic/AccountService/Public/Interface.h"
#include "BusinessLogic/PaymentService/Public/Interface.h"
#include "BusinessLogic/PriceCalculator/Public/Interface.h"
#include "Domain/ParkingReleasing.h"
#include "Domain/ParkingReservation.h"
#include "Domain/PaymentTicket.h"
#include "Domain/Vehicle.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

class AccountServiceImpl final : public Interface
{
public:
  Cmn::Result<Domain::ReservationTicket> reserveParkingSpace(const Domain::ReservationRequest &req) override;
  Cmn::Result<Domain::ReleasingResponse> releaseParkingSpace(const Domain::ReleasingRequest &req) override;
  Cmn::Result<Domain::ParkingReservation> getParkingReservation(
    const Domain::VehicleNumber &vehicleNumber) const override;

private:
  std::unordered_map<Domain::VehicleNumber, Domain::ReservationTicket> _storage;
  std::unordered_map<Domain::VehicleNumber, Domain::ParkingReservation> _reservationStorage;
  std::unordered_map<Domain::VehicleNumber, Domain::PaymentTicketID> _paymentTicketsIDs;
};

}// namespace Vertaler::ParkingSystem::BL::AccountService