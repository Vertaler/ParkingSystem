add_executable(ParkingSystem main.cpp)
target_link_libraries(ParkingSystem
  ParkingSpaceManager
  BarrierController
  Hardware
  PriceCalculator
  PaymentService
  EntryExitController
  VehicleCatalog
  scn
)
target_include_directories(ParkingSystem PRIVATE ${CMAKE_SOURCE_DIR}/src)