#pragma once

#include <string>

namespace Vertaler::ParkingSystem::Domain
{

class VehicleNumber
{
public:
  VehicleNumber() = default;
  explicit VehicleNumber(std::string data) : _data(std::move(data)) {}

  std::string asString() const
  {
    return _data;
  }

private:
  // temporary solution
  // TODO store car number in other representaion
  std::string _data;
};

struct Vehicle
{
  VehicleNumber number;
};

}// namespace Vertaler::ParkingSystem::Domain