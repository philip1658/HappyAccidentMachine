cmake_minimum_required(VERSION 3.22)

# Basic tests for HAM
enable_testing()

# Simple unit test for core components
add_executable(BasicTests
    BasicTests.cpp
)

target_link_libraries(BasicTests PRIVATE HAMLib)

add_test(NAME BasicComponentTest COMMAND BasicTests)