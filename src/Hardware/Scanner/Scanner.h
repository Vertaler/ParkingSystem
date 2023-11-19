#pragma once

#include "Common/Result.h"

namespace Vertaler::ParkingSystem::Hardware
{

class Scanner
{
public:
  struct ScannedData
  {
  };

  virtual ~Scanner() = default;
  virtual Cmn::Result<ScannedData> scan() const = 0
};

}// namespace Vertaler::ParkingSystem::Hardware