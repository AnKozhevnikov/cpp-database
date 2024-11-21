cmake_minimum_required(VERSION 3.5.0)
project(database VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(database ${SOURCES})
set_target_properties(database PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE database stdc++fs)

