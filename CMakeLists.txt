# cmake -DSDL2_DIR=lib/SDL2/cmake .. ( no longer need to this because of hints c: )
# use CMake Tools VSCode ext in order to configure project and compile for you.
cmake_minimum_required(VERSION 3.23)

project(cplay )

find_package(SDL2 REQUIRED HINTS lib/SDL2/cmake )
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(cplay src/main.cpp)
target_link_libraries(cplay ${SDL2_LIBRARIES})