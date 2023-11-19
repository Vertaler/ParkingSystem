#pragma once

#include <optional>


namespace Vertaler::Cmn
{

template<typename T> class Result
{

  const T &getResult() const
  {
    assert(_res.hasValue());
    return *_res;
  }

  void *getError() const
  {
    // TODO: Add support of errors
    return nullptr;
  }

private:
  std::optional<T> _res;
}

}// namespace Vertaler::Cmn