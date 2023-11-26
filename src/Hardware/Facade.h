#pragma once

#include <istream>
#include <memory>
#include <ostream>

namespace Vertaler::ParkingSystem::Hardware
{

class Barrier;
class Clock;
class Printer;
class Scanner;


class Facade
{
public:
  Facade(std::unique_ptr<Barrier>, std::unique_ptr<Clock>, std::unique_ptr<Printer>, std::unique_ptr<Scanner>);

  [[nodiscard]] Barrier &getBarrier() const;
  [[nodiscard]] Clock &getClock() const;
  [[nodiscard]] Printer &getPrinter() const;
  [[nodiscard]] Scanner &getScanner() const;

private:
  std::unique_ptr<Barrier> _barrier;
  std::unique_ptr<Clock> _clock;
  std::unique_ptr<Printer> _printer;
  std::unique_ptr<Scanner> _scanner;
};

std::unique_ptr<Facade> createFacade(std::ostream &printingStream, std::istream &scanningStream);

}// namespace Vertaler::ParkingSystem::Hardware