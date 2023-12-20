#pragma once

#include "Concepts.h"

#include <optional>
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
  explicit Error(ErrType enumErrCode) : _errCode(makeErrorCode(enumErrCode))
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

  Error &withNested(Error err) noexcept
  {
    _nested.reset(new Error(std::move(err)));
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
  // std::source_location _sourceLocation;
  std::unique_ptr<Error> _nested;// Can't use optional recursively
};

}// namespace Vertaler::Cmn