set(ACCOUNT_SERVICE_SRC 
    Private/AccountServiceImpl.cpp
    Private/AccountServiceImpl.h
    Private/Factory.cpp
)

add_library(AccountService ${ACCOUNT_SERVICE_SRC})
target_include_directories(AccountService PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(AccountService PriceCalculator)

target_sources(ParkingTests PRIVATE Tests/Test.cpp)