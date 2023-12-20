#pragma once

#include "Domain/Money.h"

#include <optional>
#include <string>

namespace Vertaler::ParkingSystem::Domain
{

using PaymentTicketID = std::string;

struct PaymentTicket
{
  Money parkingPrice;
  PaymentTicketID ID;
};

using PaymentTicketOpt = std::optional<PaymentTicket>;

}// namespace Vertaler::ParkingSystem::Domain