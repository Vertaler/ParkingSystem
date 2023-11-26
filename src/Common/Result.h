#pragma once

#include <cassert>
#include <concepts>
#include <optional>
#include <type_traits>

namespace Vertaler::Cmn
{


// TODO: On my mac STD headers points to OSX platform SDK
// Which has quite old version and doesn't have concept implementation
// So we workaround it with
namespace Detail
{
  template<class T, class... Args>
  concept ConstructibleFrom = std::is_nothrow_destructible_v<T> && std::is_constructible_v<T, Args...>;
}

template<typename T> class Result
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
  requires Detail::ConstructibleFrom<T, Args...>
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

template<> class Result<void>
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