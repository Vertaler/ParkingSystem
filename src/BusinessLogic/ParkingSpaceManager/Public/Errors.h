#pragma once

#include "Common/Error.h"
namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager
{

enum class Errc
{
  ReservationNotFound
};

inline std::string_view errDomain()
{
  static const std::string_view domain = "ParkingSpaceManager";
  return domain;
}

inline Cmn::ErrorCode makeErrorCode(Errc errCodeEnum)
{
  return { errDomain(), errCodeEnum };
}

}// namespace Vertaler::ParkingSystem::BL::ParkingSpaceManager