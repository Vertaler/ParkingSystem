#include "AccountServiceImpl.h"

#include <unordered_map>

namespace Vertaler::ParkingSystem::BL::AccountService
{

AccountServiceImpl::AccountServiceImpl(const PriceCalculator::Interface &priceCalculator)
  : _priceCalculator(priceCalculator)
{}

Cmn::Result<Domain::ReservationTicket> AccountServiceImpl::reserveParkingSpace(
  const Domain::ReservationRequest & /*unused*/)
{
  return {};
}

Cmn::Result<Domain::PaymentTicket> AccountServiceImpl::releaseParkingSpace(const Domain::ReleasingRequest & /*unused*/)
{
  return {};
}


}// namespace Vertaler::ParkingSystem::BL::AccountService