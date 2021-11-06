cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(fem)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(VTK REQUIRED)

if (NOT VTK_FOUND)
    message("Skipping FEM: ${VTK_NOT_FOUND_MESSAGE}")
    return()
endif()

message(STATUS "VTK_VERSION: ${VTK_VERSION}")

file(GLOB SRC *.cpp)

add_executable(fem ${SRC})

target_link_libraries(fem Eigen3::Eigen)
target_link_libraries(fem ${VTK_LIBRARIES})
vtk_module_autoinit(
    TARGETS fem
    MODULES ${VTK_LIBRARIES}
)
