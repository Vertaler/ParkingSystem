#pragma once

#include "Domain/Money.h"

#include <string>

namespace Vertaler::ParkingSystem::Domain
{

using PaymentTicketID = std::string;

struct PaymentTicket
{
  Money parkingPrice;
  PaymentTicketID ID;
};

}// namespace Vertaler::ParkingSystem::Domain