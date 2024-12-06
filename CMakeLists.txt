cmake_minimum_required(VERSION 3.14.0)
project(database VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(ExternalProject)

set(FLEX_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/flex)

#This is used if you want to build flex from sources
#[[
ExternalProject_Add(
    flex-build
    URL https://github.com/westes/flex/releases/download/v2.6.4/flex-2.6.4.tar.gz
    CONFIGURE_COMMAND ./configure --prefix=${FLEX_INSTALL_DIR}
    BUILD_COMMAND make 
    BUILD_IN_SOURCE 1
)
]]#

set(FLEX_INCLUDE_DIR ${FLEX_INSTALL_DIR}/include)
set(FLEX_LIBRARIES ${FLEX_INSTALL_DIR}/lib/libfl.a)

include_directories(include src ${FLEX_INCLUDE_DIR})

add_subdirectory(tests)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(database ${SOURCES})
set_target_properties(database PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(database PRIVATE stdc++fs ${FLEX_LIBRARIES})

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE database)

#This is used if you want to build flex from sources
#add_dependencies(database flex-build)