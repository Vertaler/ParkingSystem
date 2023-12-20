#pragma once

#include <cstddef>

namespace Vertaler::ParkingSystem::Domain
{

struct Money
{
  size_t amount = 0;

  friend Money operator+(const Money &lhs, const Money &rhs)
  {
    Money res{ lhs.amount + rhs.amount };
    return res;
  }

  template<typename T> friend Money operator*(const T &lhs, const Money &rhs)
  {
    Money res{ static_cast<size_t>(lhs * rhs.amount) };
    return res;
  }
};

}// namespace Vertaler::ParkingSystem::Domain