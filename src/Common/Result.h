#pragma once

#include "Concepts.h"

#include <cassert>
#include <optional>

namespace Vertaler::Cmn
{


template<typename T>
class Result
{
public:
  // TODO: Just temporary. Need remove it.
  Result() = default;

  // Don't make explicit because we want implicit conversion
  // NOLINTBEGIN(hicpp-explicit-conversions)
  Result(const T &val) : _res(val) {}
  Result(T &&val) : _res(val) {}
  // NOLINTEND(hicpp-explicit-conversions)

  template<typename... Args>
  requires ConstructibleFrom<T, Args...>
  explicit Result(Args &&...args)
  {
    _res.emplace(std::forward<Args>(args)...);
  }

  [[nodiscard]] const T &getResult() const
  {
    assert(_res.has_value());
    return *_res;
  }

  [[nodiscard]] void *getError() const
  {
    // TODO: Add support of errors
    return nullptr;
  }

private:
  std::optional<T> _res;
};

template<>
class Result<void>
{
public:
  void getResult() const {}
  [[nodiscard]] void *getError() const
  {
    // TODO: Add support of errors
    return nullptr;
  }
};


}// namespace Vertaler::Cmn