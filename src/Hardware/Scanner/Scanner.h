#pragma once

#include "Common/Result.h"

#include <string>

namespace Vertaler::ParkingSystem::Hardware
{

class Scanner
{
public:
  struct ScannedData
  {
    std::string data;
  };

  virtual ~Scanner() = default;
  [[nodiscard]] virtual Cmn::Result<ScannedData> scan() const = 0;
};

}// namespace Vertaler::ParkingSystem::Hardware