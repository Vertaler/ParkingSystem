#include "Facade.h"

#include "Barrier/Barrier.h"
#include "Barrier/Factory.h"
#include "Clock/Clock.h"
#include "Clock/Factory.h"
#include "Printer/Factory.h"
#include "Printer/Printer.h"
#include "Scanner/Factory.h"
#include "Scanner/Scanner.h"

namespace Vertaler::ParkingSystem::Hardware
{

Facade::Facade(std::unique_ptr<Barrier> barrier,
  std::unique_ptr<Clock> clock,
  std::unique_ptr<Printer> printer,
  std::unique_ptr<Scanner> scanner)
  : _barrier(std::move(barrier)), _clock(std::move(clock)), _printer(std::move(printer)), _scanner(std::move(scanner))
{}

Barrier &Facade::getBarrier() const
{
  return *_barrier;
}

Clock &Facade::getClock() const
{
  return *_clock;
}

Printer &Facade::getPrinter() const
{
  return *_printer;
}

Scanner &Facade::getScanner() const
{
  return *_scanner;
}

std::unique_ptr<Facade> createFacade(std::ostream &printingStream, std::istream &scanningStream)
{
  return std::make_unique<Facade>(
    createBarrier(), createClock(), createPrinter(printingStream), createScanner(scanningStream));
}

}// namespace Vertaler::ParkingSystem::Hardware