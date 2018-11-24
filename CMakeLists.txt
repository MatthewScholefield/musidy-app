cmake_minimum_required(VERSION 3.12)
project(musidy)

set(CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
find_package(SDL2 REQUIRED)
pkg_check_modules(PORTAUDIO portaudio-2.0)
pkg_check_modules(PORTAUDIOCPP portaudiocpp)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PORTAUDIO_INCLUDE_DIRS})
add_executable(
        musidy
        source/Renderer.cpp
        source/SdlWindow.cpp
        source/SoundSystem.cpp
        source/main.cpp
)

target_link_libraries(musidy ${SDL2_LIBRARIES})
target_link_libraries(musidy ${PORTAUDIOCPP_LIBRARIES})
