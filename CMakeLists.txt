# cmake -DSDL2_DIR=lib/SDL2/cmake ..
cmake_minimum_required(VERSION 3.23)

project(cplay )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(cplay src/main.cpp)
target_link_libraries(cplay ${SDL2_LIBRARIES})