#include "Factory.h"
#include "Scanner.h"

namespace Vertaler::ParkingSystem::Hardware
{

class ScannerImpl : public Scanner
{
public:
  explicit ScannerImpl(std::istream &scanningStream) : _scanningStream(scanningStream) {}
  [[nodiscard]] Cmn::Result<ScannedData> scan() const override
  {
    ScannedData result;
    _scanningStream >> result.data;
    return Cmn::Result<ScannedData>{ result };
  }

private:
  std::istream &_scanningStream;
};

std::unique_ptr<Scanner> createScanner(std::istream &scanningStream)
{
  return std::make_unique<ScannerImpl>(scanningStream);
}

}// namespace Vertaler::ParkingSystem::Hardware