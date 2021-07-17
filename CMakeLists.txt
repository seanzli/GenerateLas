cmake_minimum_required(VERSION 3.0.0)
project(GenerateLas VERSION 0.1.0)

set(DEBUG_MODE 1)

include(CTest)
enable_testing()

include_directories(./include)

# glog
find_package(Glog REQUIRED)
include_directories(BEFORE ${GLOG_INCLUDE_DIRS}) 

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} -lglog -lgflags -lpthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
