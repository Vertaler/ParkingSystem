set(ACCOUNT_SERVICE_SRC 
    Private/ParkingSpaceManagerImpl.cpp
    Private/ParkingSpaceManagerImpl.h
    Private/Factory.cpp
)

add_library(ParkingSpaceManager ${ACCOUNT_SERVICE_SRC})
target_include_directories(ParkingSpaceManager PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ParkingSpaceManager EntryExitController)

target_sources(ParkingTests PRIVATE Tests/Test.cpp)