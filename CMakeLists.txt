cmake_minimum_required(VERSION 3.12)
project(musidy)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(musidy source/main.cpp source/Renderer.cpp source/Renderer.hpp source/SdlWindow.cpp source/SdlWindow.hpp)

target_link_libraries(musidy ${SDL2_LIBRARIES})
