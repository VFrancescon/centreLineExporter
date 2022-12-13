cmake_minimum_required(VERSION 3.1.0)
project(centreLineExporter) ##EDIT THIS WITH YOUR PROJECT NAME

## S0: Some boilerplate
add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## S1: Finding prebuilt packages
find_package( OpenCV REQUIRED )
find_package(Pylon QUIET)
if (NOT ${Pylon_FOUND})
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindPylon.cmake")
endif()
find_package(Threads REQUIRED)

## S3: Set variables for library linkage. Use one of the below only
set(VisionLibs ${Pylon_LIBRARIES} ${OpenCV_LIBS} )
set(EIGEN Eigen3::Eigen)
set(THREADS Threads::Threads)

## S4: Set include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/opt/pylon/include)

add_executable(centreLineOut "centreLineExporter.cpp")
target_link_libraries(centreLineOut ${VisionLibs})