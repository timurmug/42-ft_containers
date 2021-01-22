cmake_minimum_required(VERSION 3.4)
project(GoogleTestDemo)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
add_subdirectory(unit_tests/googletest)

include_directories(unit_tests/googletest/googletest/include
                    includes/)
set(SRCS    unit_tests/ListTests.cpp
            unit_tests/StackTests.cpp
            unit_tests/QueueTests.cpp
            unit_tests/VectorTests.cpp
            unit_tests/DequeTests.cpp)
#set(SRCS unit_tests/VectorTests.cpp)

add_executable(UnitTests ${SRCS})
target_link_libraries(UnitTests gtest gtest_main)
