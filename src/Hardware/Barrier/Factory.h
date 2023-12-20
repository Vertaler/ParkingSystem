#pragma once

namespace Vertaler::ParkingSystem::Hardware
{

class Barrier;
std::unique_ptr<Barrier> createBarrier();

}// namespace Vertaler::ParkingSystem::Hardware