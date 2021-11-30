cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(fem)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    )

FetchContent_MakeAvailable(googletest)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(VTK REQUIRED)

if (NOT VTK_FOUND)
    message("Skipping FEM: ${VTK_NOT_FOUND_MESSAGE}")
    return()
endif()

message(STATUS "VTK_VERSION: ${VTK_VERSION}")

add_subdirectory(src)
add_subdirectory(test)

