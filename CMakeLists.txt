
cmake_minimum_required(VERSION 3.16...3.27)

project(ConsoleCarRental)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(ConsoleCarRental
    main.cpp
    ${SOURCES}
)

target_include_directories(ConsoleCarRental PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
)

target_link_libraries(ConsoleCarRental PRIVATE Qt6::Core)
