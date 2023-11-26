#include "Factory.h"
#include "Printer.h"

namespace Vertaler::ParkingSystem::Hardware
{

class PrinterImpl : public Printer
{
public:
  explicit PrinterImpl(std::ostream &printingStream) : _printingStream(printingStream) {}
  [[nodiscard]] Cmn::Result<void> print(const PrintingInfo &info) const override
  {
    _printingStream << info.data << std::endl;
    return {};
  }

private:
  std::ostream &_printingStream;
};

std::unique_ptr<Printer> createPrinter(std::ostream &printingStream)
{
  return std::make_unique<PrinterImpl>(printingStream);
}

}// namespace Vertaler::ParkingSystem::Hardware