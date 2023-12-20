set(BARRIER_CONTROLLER_SRC 
    Private/BarrierControllerBase.h
    Private/BarrierControllerBase.cpp
    Private/InputBarrierController.h
    Private/InputBarrierController.cpp
    Private/OutputBarrierController.h
    Private/OutputBarrierController.cpp
    Private/Factory.cpp
)

add_library(BarrierController ${BARRIER_CONTROLLER_SRC})
target_include_directories(BarrierController PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(BarrierController 
    AccountService 
    Hardware
    fmt::fmt
 )