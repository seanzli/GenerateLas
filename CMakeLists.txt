cmake_minimum_required(VERSION 3.0.0)
project(GenerateLas VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

set(DEBUG_MODE 1)

include(CTest)
enable_testing()

include_directories(./include)
include_directories(./Test)

# glog
find_package(Glog REQUIRED)
include_directories(BEFORE ${GLOG_INCLUDE_DIRS}) 



add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} -lglog -lgflags -lpthread ${GTEST_BOTH_LIBRARIES})