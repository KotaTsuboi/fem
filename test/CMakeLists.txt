project(test)

enable_testing()

file(GLOB SRC ../src/material/*.cpp)
file(GLOB TEST_SRC */*.cpp)

add_executable(test ${SRC} ${TEST_SRC})

target_link_libraries(test gtest_main gmock_main Eigen3::Eigen)

add_test(NAME test COMMAND test)

include(GoogleTest)

gtest_discover_tests(test)

