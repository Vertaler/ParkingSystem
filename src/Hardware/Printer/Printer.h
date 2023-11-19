#pragma once

#include "Common/Result.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Printer
{
public:
  struct PrintingInfo
  {
  };

  virtual ~Printer() = default;
  virtual Cmn::Result<void> print(const PrintingInfo &info) const = 0
};

}// namespace Vertaler::ParkingSystem::Hardware