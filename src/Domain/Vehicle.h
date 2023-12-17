#pragma once

#include <functional>
#include <ostream>
#include <string>


namespace Vertaler::ParkingSystem::Domain
{

class VehicleNumber
{
public:
  VehicleNumber() = default;
  explicit VehicleNumber(std::string data) : _data(std::move(data)) {}

  [[nodiscard]] std::string asString() const
  {
    return _data;
  }

  [[nodiscard]] friend auto operator==(const VehicleNumber &lhs, const VehicleNumber &rhs) noexcept
  {
    return rhs._data == lhs._data;
  }
  friend std::ostream &operator<<(std::ostream &out, const VehicleNumber &vehicleNumber)
  {
    return out << vehicleNumber._data;
  }

  friend std::hash<VehicleNumber>;

private:
  // temporary solution
  // TODO store car number in other representaion
  std::string _data;
};

enum class VehicleServiceCategory
{
  General,
  Police,
  Ambulance
};

struct Vehicle
{
  VehicleNumber number;
  VehicleServiceCategory serviceCategory{ VehicleServiceCategory::General };
};

}// namespace Vertaler::ParkingSystem::Domain

namespace std
{

template<>
struct std::hash<Vertaler::ParkingSystem::Domain::VehicleNumber>
{
  std::size_t operator()(const Vertaler::ParkingSystem::Domain::VehicleNumber &number) const noexcept
  {
    return std::hash<std::string>{}(number._data);
  }
};

}// namespace std
