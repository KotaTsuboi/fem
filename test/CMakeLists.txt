project(test)

enable_testing()

add_executable(test test_add.cpp)

target_link_libraries(test PRIVATE gtest_main)

add_test(NAME test COMMAND test)

include(GoogleTest)

gtest_discover_tests(test)

