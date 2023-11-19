#pragma once

#include <string>

namespace Vertaler::ParkingSystem::Domain
{

class CarNumber
{
  explicit CarNumber(std::string data) : _data(std::move(data)) {}

  std::string asString() const { return _data; }

private:
  // temporary solution
  // TODO store car number in other representaion
  std::string _data;
};

struct CarInfo
{
  CarNumber number;
};

}// namespace Vertaler::ParkingSystem::Domain