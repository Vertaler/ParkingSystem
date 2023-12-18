#pragma once

#include "Common/Error.h"

namespace Vertaler::ParkingSystem::BL::PaymentService
{

enum class Errc
{
  PaymentTicketNotFound,
  PriceCalculatorError,
  AccountServiceError
};

inline std::string_view errDomain()
{
  static const std::string_view domain = "PaymentService";
  return domain;
}

inline Cmn::ErrorCode makeErrorCode(Errc errCodeEnum)
{
  return { errDomain(), errCodeEnum };
}

}// namespace Vertaler::ParkingSystem::BL::PaymentService