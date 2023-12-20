#pragma once

#include "Domain/Vehicle.h"
#include <unordered_set>

namespace Vertaler::ParkingSystem::BL::EntryExitController
{

inline bool isEmergencyService(Domain::VehicleServiceCategory serviceCategory)
{
  static const std::unordered_set emergencyServices{
    Domain::VehicleServiceCategory::Ambulance,
    Domain::VehicleServiceCategory::Police,
  };

  return emergencyServices.contains(serviceCategory);
}
}// namespace Vertaler::ParkingSystem::BL::EntryExitController