add_executable(ParkingSystem main.cpp)
target_link_libraries(ParkingSystem
  AccountService
  BarrierController
  Hardware
  PriceCalculator
  scn
)
target_include_directories(ParkingSystem PRIVATE ${CMAKE_SOURCE_DIR}/src)