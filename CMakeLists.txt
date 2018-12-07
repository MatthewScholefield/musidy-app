cmake_minimum_required(VERSION 3.12)
project(musidy)

set(CMAKE_CXX_STANDARD 14)

include(FindPkgConfig)
find_package(SDL2 REQUIRED)
pkg_check_modules(PORTAUDIO portaudio-2.0)
pkg_check_modules(PORTAUDIOCPP portaudiocpp)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PORTAUDIO_INCLUDE_DIRS})
add_library(
        musidy_common
        source/Renderer.cpp
        source/SdlWindow.cpp
        source/SoundSystem.cpp
        source/libs/tsf.cpp
        source/Instrument.cpp
        source/SongGenerator.cpp
        source/utils.cpp
        source/Interface.cpp
        source/ParticleSystem.cpp source/ParticleSystem.hpp)
add_executable(
        musidy
        source/main.cpp
)
add_executable(
        tests
        tests/TestSongGenerator.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/libs)

target_link_libraries(musidy musidy_common)
target_link_libraries(musidy ${SDL2_LIBRARIES})
target_link_libraries(musidy ${PORTAUDIOCPP_LIBRARIES})
target_link_libraries(tests musidy_common)
