cmake_minimum_required(VERSION 3.14.0)
project(database VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(database ${SOURCES})
set_target_properties(database PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(database PRIVATE stdc++fs)

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE database)

include(GoogleTest)
add_executable(sampletest tests/sampletest.cpp)
target_link_libraries(sampletest PRIVATE database gtest_main)