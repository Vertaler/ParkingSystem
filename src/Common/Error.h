#pragma once

#include "Concepts.h"

#include <memory>
#include <source_location>
#include <string>
#include <string_view>

namespace Vertaler::Cmn
{

struct ErrorCode
{
public:
  template<Enum ValueType>
  ErrorCode(std::string_view domain, ValueType val) : _domain(domain), _value(static_cast<size_t>(val))
  {}

  [[nodiscard]] const std::string_view domain() const noexcept
  {
    return _domain;
  }
  [[nodiscard]] size_t value() const noexcept
  {
    return _value;
  }
  friend auto operator<=>(const ErrorCode &lhs, const ErrorCode &rhs) noexcept = default;

private:
  std::string_view _domain;
  size_t _value{};
};

class Error
{
public:
  template<Enum ErrType>
  explicit Error(ErrType enumErrCode, std::source_location sourceLocation = std::source_location::current())
    : _errCode(makeErrorCode(enumErrCode)), _sourceLocation(std::move(sourceLocation))
  {}

  [[nodiscard]] const Error *getNested() const noexcept
  {
    return _nested.get();
  }

  template<Enum ErrType>
  [[nodiscard]] bool is(ErrType enumErrCode) const noexcept
  {
    return _errCode == makeErrorCode(enumErrCode);
  }

  const std::source_location &sourceLocation() const noexcept
  {
    return _sourceLocation;
  }

  Error &withNested(Error &&err) noexcept
  {
    _nested = std::make_unique<Error>(std::move(err));
    return *this;
  }

  Error &withMessage(std::string message) noexcept
  {
    _message = std::move(message);
    return *this;
  }


private:
  ErrorCode _errCode;
  std::string _message;
  std::source_location _sourceLocation;
  std::unique_ptr<Error> _nested;// Can't use optional recursively
};

// General error codes
enum class Errc
{
  DependencyError// Error caused by error in other componet
};

inline std::string_view errDomain()
{
  static const std::string_view domain = "General";
  return domain;
}

inline Cmn::ErrorCode makeErrorCode(Errc errCodeEnum)
{
  return { errDomain(), errCodeEnum };
}

// TODO: Simplify code for making nested errors.
// Probably need to create custom copy ctor
#define CMN_NESTED_ERR(errCode, nested)                                                \
  {                                                                                    \
    std::move(Cmn::Error(Cmn::Errc::DependencyError).withNested(std::move(*(nested)))) \
  }

#define CMN_HANDLE_DEPENDENCY_ERR(result)                   \
  if (auto *err = (result).getError(); err != nullptr)      \
  {                                                         \
    return CMN_NESTED_ERR(Cmn::Errc::DependencyError, err); \
  }


}// namespace Vertaler::Cmn