#pragma once

#include "BusinessLogic/VehicleCatalog/Public/Interface.h"

namespace Vertaler::ParkingSystem::BL::VehicleCatalog
{
class VehicleCatalogImpl : public Interface
{
public:
  [[nodiscard]] Cmn::Result<Domain::Vehicle> receiveVehicleInfo(const Domain::VehicleNumber &number) const override;
};
}// namespace Vertaler::ParkingSystem::BL::VehicleCatalog
