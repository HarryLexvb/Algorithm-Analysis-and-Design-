cmake_minimum_required(VERSION 3.24)
project(AudioVisualizer_FFT_linux)

set(CMAKE_CXX_STANDARD 23)

if (UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_definitions(-DDEBUG=1)
    elseif (CMAKE_BUILD_TYPE MATCHES Release)
        add_definitions(-DRELEASE=1)
    endif ()
endif ()

add_library(
        audio-visualizer
        AudioVisualizer.cpp
        AudioVisualizer.h
)

add_executable(AudioVisualizer_FFT_linux main.cpp AudioVisualizer.cpp AudioVisualizer.h Application.h Application.cpp)

target_link_libraries(AudioVisualizer_FFT_linux audio-visualizer sfml-audio sfml-system sfml-window sfml-graphics)
