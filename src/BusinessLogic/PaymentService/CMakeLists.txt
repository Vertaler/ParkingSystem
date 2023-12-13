set(PAYMENT_SERVICE_SRC 
    Private/PaymentServiceImpl.cpp
    Private/PaymentServiceImpl.h
    Private/Factory.cpp
)

add_library(PaymentService ${PAYMENT_SERVICE_SRC})
target_include_directories(PaymentService PRIVATE ${CMAKE_SOURCE_DIR}/src)