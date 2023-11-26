#pragma once

#include "Common/Result.h"

#include <string>

namespace Vertaler::ParkingSystem::Hardware
{

class Printer
{
public:
  struct PrintingInfo
  {
    std::string data;
  };

  virtual ~Printer() = default;
  virtual Cmn::Result<void> print(const PrintingInfo &info) const = 0;
};

}// namespace Vertaler::ParkingSystem::Hardware