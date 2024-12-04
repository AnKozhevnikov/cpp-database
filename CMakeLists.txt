cmake_minimum_required(VERSION 3.14.0)
project(database VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(FLEX REQUIRED)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(NOT FLEX_INCLUDE_DIRS)
        set(FLEX_INCLUDE_DIRS /usr/include)
    endif()
    if(NOT FL_LIBRARY)
        set(FL_LIBRARY /usr/lib/x86_64-linux-gnu/libfl.so)
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if(NOT FLEX_INCLUDE_DIRS)
        set(FLEX_INCLUDE_DIRS C:/path/to/flex/include)
    endif()
    if(NOT FL_LIBRARY)
        set(FL_LIBRARY C:/path/to/flex/lib/fl.lib)
    endif()
endif()

include_directories(include src)

add_subdirectory(tests)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(database ${SOURCES})
set_target_properties(database PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(database PRIVATE stdc++fs)

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE database)