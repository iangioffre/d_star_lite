
project(HW9)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O0")
set(CMAKE_BUILD_TYPE Debug)

# locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create unit test executable
add_executable(test_d_star
               graph.cpp
               test_d_star.cpp
               adjacency_list.cpp
               adjacency_matrix.cpp)
target_link_libraries(test_d_star ${GTEST_LIBRARIES} pthread)

