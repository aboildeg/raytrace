cmake_minimum_required(VERSION 3.10.0)
project(raytrace VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

add_executable(raytrace src/main.cpp)

include(CTest)
enable_testing()

