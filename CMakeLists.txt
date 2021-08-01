cmake_minimum_required(VERSION 3.0.0)
project(GenerateLas VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

set(DEBUG_MODE 1)

include(CTest)
enable_testing()

include_directories(./include)
include_directories(./Test)
include_directories(./3rd)
include_directories(./3rd/LAStools/LASlib/inc)
include_directories(./3rd/LAStools/LASzip/src)

# glog
find_package(glog 0.5.0 REQUIRED)

# lastool
link_directories(./3rd/LAStools/LASlib/lib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} -lglog -lgflags -lpthread)
target_link_libraries(${PROJECT_NAME} -lLASlib)
