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




file(GLOB SRC src/core/*/*.cpp)

message("Source: ${SRC}")

add_library(fem_core ${SRC})
target_link_libraries(fem_core Eigen3::Eigen)
target_link_libraries(fem_core ${VTK_LIBRARIES})
vtk_module_autoinit(
    TARGETS fem_core
    MODULES ${VTK_LIBRARIES}
)

add_executable(simple src/example/simple.cpp)
target_link_libraries(simple fem_core)
set_target_properties(simple PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(five_elements src/example/five_elements.cpp)
target_link_libraries(five_elements fem_core)
set_target_properties(five_elements PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(auto_mesh src/example/auto_mesh.cpp)
target_link_libraries(auto_mesh fem_core)
set_target_properties(auto_mesh PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


file(GLOB TEST_SRC test/*/*.cpp)

add_executable(test ${TEST_SRC})

target_link_libraries(test gtest_main gmock_main fem_core)

set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_test(NAME test COMMAND test)

include(GoogleTest)

gtest_discover_tests(test)

