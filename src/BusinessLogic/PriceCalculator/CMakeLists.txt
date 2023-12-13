set(PRICE_CALCULATOR_SRC 
    Private/Factory.cpp
    Private/PriceCalculatorImpl.cpp
    Private/PriceCalculatorImpl.h
    Private/Rates.cpp
    Private/Rates.h
)

add_library(PriceCalculator ${PRICE_CALCULATOR_SRC})
target_include_directories(PriceCalculator PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_sources(ParkingTests PRIVATE Tests/Test.cpp)