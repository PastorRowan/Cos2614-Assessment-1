
cmake_minimum_required(VERSION 3.16...3.27)

project(ConsoleCarRental)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(HEADERS
    inc/App.h
    inc/helpers.h
    inc/VehiclesFile.h
    inc/pages/AddCarPage.h
    inc/pages/AddMotorcyclePage.h
    inc/pages/DisplayAllVehiclesPage.h
    inc/pages/DisplayAvailableVehiclesOnlyPage.h
    inc/pages/helpers.h
    inc/pages/HomePage.h
    inc/pages/Id.h
    inc/pages/Page.h
    inc/pages/pages.h
    inc/pages/RentVehiclePage.h
    inc/pages/ReturnVehiclePage.h
    inc/pages/SearchVehicleByIdPage.h
    inc/vehicles/Car.h
    inc/vehicles/Motorcycle.h
    inc/vehicles/Vehicle.h
    inc/vehicles/vehicles.h
)

set(SOURCES
    src/App.cpp
    src/helpers.cpp
    src/pages/AddCarPage.cpp
    src/pages/AddMotorcyclePage.cpp
    src/pages/DisplayAllVehiclesPage.cpp
    src/pages/DisplayAvailableVehiclesOnlyPage.cpp
    src/pages/helpers.cpp
    src/pages/HomePage.cpp
    src/pages/RentVehiclePage.cpp
    src/pages/ReturnVehiclePage.cpp
    src/pages/SearchVehicleById.cpp
    src/vehicles/Car.cpp
    src/vehicles/Motorcycle.cpp
    src/vehicles/Vehicle.cpp
    src/VehiclesFile/addCar.cpp
    src/VehiclesFile/addMotorcycle.cpp
    src/VehiclesFile/composeAllVehicles.cpp
    src/VehiclesFile/composeAvailableVehiclesOnly.cpp
    src/VehiclesFile/core.cpp
    src/VehiclesFile/fileIO.cpp
    src/VehiclesFile/rentVehicleById.cpp
    src/VehiclesFile/returnVehicleById.cpp
    src/VehiclesFile/searchVehicleById.cpp
)

add_executable(ConsoleCarRental
    main.cpp
)

target_include_directories(ConsoleCarRental PRIVATE
    inc
)

target_sources(ConsoleCarRental PRIVATE
    main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(ConsoleCarRental PRIVATE Qt6::Core)
