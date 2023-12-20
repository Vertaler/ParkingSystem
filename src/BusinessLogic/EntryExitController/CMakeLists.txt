set(ENTRY_EXIT_CONTROLLER_SRC 
    Private/EntryExitControllerImpl.cpp
    Private/EntryExitControllerImpl.h
    Private/Factory.cpp
)

add_library(EntryExitController ${ENTRY_EXIT_CONTROLLER_SRC})
target_include_directories(EntryExitController PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(EntryExitController PaymentService VehicleCatalog)