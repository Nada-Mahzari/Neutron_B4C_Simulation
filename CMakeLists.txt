
cmake_minimum_required(VERSION 3.16)

project(Neutron_B4C_Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geant4 11.2 REQUIRED)

message(STATUS "Geant4 version: ${Geant4_VERSION}")
message(STATUS "Geant4 libraries: ${Geant4_LIBRARIES}")
message(STATUS "Geant4 found successfully!")

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

list(FILTER SOURCES EXCLUDE REGEX "/(\\.#|#)")

add_executable(Neutron_B4C_Simulation
    ${SOURCES}
)

target_link_libraries(Neutron_B4C_Simulation
    ${Geant4_LIBRARIES}
)
