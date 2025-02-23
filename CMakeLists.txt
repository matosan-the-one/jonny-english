cmake_minimum_required(VERSION 3.20)

project(Game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

option(DEBUG "Build with debug flags" OFF)
option(RELEASE "Build with release flags" OFF)

if(DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -g -O0") 
endif()

if(RELEASE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB src src/*.cpp)

add_executable(game ${src} src/main.cpp)

target_link_libraries(game PUBLIC
    sdl2
)
