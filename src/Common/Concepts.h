#pragma once

#include <ostream>
#include <type_traits>

namespace Vertaler::Cmn
{

// TODO: On my mac STD headers points to OSX platform SDK
// Which has quite old version and doesn't have concept implementation
// So we workaround it with own implementation of needed standard concepts


template<class T, class... Args>
concept ConstructibleFrom = std::is_nothrow_destructible_v<T> && std::is_constructible_v<T, Args...>;

template<typename T>
concept Enum = std::is_enum_v<T>;


}// namespace Vertaler::Cmn