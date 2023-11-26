#pragma once

#include <memory>

namespace Vertaler::ParkingSystem::Hardware
{
class Facade;
}

namespace Vertaler::ParkingSystem::BL::AccountService
{
class Interface;
}

namespace Vertaler::ParkingSystem::BL::BarrierController
{

class Interface;
std::unique_ptr<Interface> createInputContoller(Hardware::Facade &hardware, AccountService::Interface &accountService);
std::unique_ptr<Interface> createOutputContoller(Hardware::Facade &hardware, AccountService::Interface &accountService);

}// namespace Vertaler::ParkingSystem::BL::BarrierController