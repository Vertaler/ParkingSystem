#pragma once

namespace Vertaler::Cmn
{
template<typename... Interfaces>
class CompositeInterface : public Interfaces...
{
};
}// namespace Vertaler::Cmn