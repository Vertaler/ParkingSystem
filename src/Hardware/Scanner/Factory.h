#pragma once

#include <istream>
#include <memory>


namespace Vertaler::ParkingSystem::Hardware
{

class Scanner;
std::unique_ptr<Scanner> createScanner(std::istream &scanningStream);

}// namespace Vertaler::ParkingSystem::Hardware