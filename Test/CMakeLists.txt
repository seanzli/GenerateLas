cmake_minimum_required(VERSION 3.0.0)
project(TestUnit VERSION 0.1.0)

enable_testing()

# include directory
include_directories(../include)

# gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# src
aux_source_directory(./ SRC_LIST)

# test exe
add_executable(${PROJECT_NAME} ${SRC_LIST})

# link libraries
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
gtest_discover_tests(${PROJECT_NAME})
