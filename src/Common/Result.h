#pragma once

#include "Concepts.h"
#include "Error.h"

#include <cassert>
#include <memory>
#include <optional>
#include <type_traits>
#include <variant>

namespace Vertaler::Cmn
{


template<typename T>
class Result
{
public:
  // TODO: Just temporary. Need remove it.

  // Don't make explicit because we want implicit conversion
  // NOLINTBEGIN(hicpp-explicit-conversions)
  Result(const T &val) : _res(val) {}
  Result(T &&val) : _res(val) {}
  // NOLINTEND(hicpp-explicit-conversions)

  template<typename... Args>
  requires ConstructibleFrom<T, Args...>
  explicit Result(Args &&...args)
  {
    _res.template emplace<T>(std::forward<Args>(args)...);
  }

  Result(Error err)
  {
    _res.template emplace<Error>(std::move(err));
  }

  [[nodiscard]] T getResult() const
  {
    assert(std::holds_alternative<T>(_res));
    return std::get<T>(_res);
  }

  [[nodiscard]] const Error *getError() const noexcept
  {
    return std::get_if<Error>(&_res);
  }

  [[nodiscard]] Error *getError() noexcept
  {
    return std::get_if<Error>(&_res);
  }

private:
  std::variant<T, Error> _res;
};

template<>
class Result<void>
{
public:
  Result() = default;
  Result(Error err)
  {
    _err.emplace(std::move(err));
  }

  [[nodiscard]] Error *getError() noexcept
  {
    if (_err.has_value())
    {
      return &_err.value();
    }

    return nullptr;
  }

  [[nodiscard]] const Error *getError() const noexcept
  {
    return const_cast<Result *>(this)->getError();
  }


private:
  std::optional<Error> _err;
};


}// namespace Vertaler::Cmn