set(VEHICLE_CATALOG_SRC 
    Private/Factory.cpp
    Private/VehicleCatalogImpl.cpp
    Private/VehicleCatalogImpl.h
)

add_library(VehicleCatalog ${VEHICLE_CATALOG_SRC})
target_include_directories(VehicleCatalog PRIVATE ${CMAKE_SOURCE_DIR}/src)