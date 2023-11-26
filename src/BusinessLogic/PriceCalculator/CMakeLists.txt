set(PRICE_CALCULATOR_SRC 
    Private/PriceCalculatorImpl.cpp
    Private/PriceCalculatorImpl.h
)

add_library(PriceCalculator ${PRICE_CALCULATOR_SRC})
target_include_directories(PriceCalculator PRIVATE ${CMAKE_SOURCE_DIR}/src)