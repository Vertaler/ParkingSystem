#pragma once

#include <memory>
#include <ostream>


namespace Vertaler::ParkingSystem::Hardware
{

class Printer;
std::unique_ptr<Printer> createPrinter(std::ostream &printingStream);

}// namespace Vertaler::ParkingSystem::Hardware