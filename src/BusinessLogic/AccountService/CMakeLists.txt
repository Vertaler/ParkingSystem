set(ACCOUNT_SERVICE_SRC 
    Private/AccountServiceImpl.cpp
    Private/AccountServiceImpl.h
)

add_library(AccountService ${ACCOUNT_SERVICE_SRC})
target_include_directories(AccountService PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(AccountService PriceCalculator)