cmake_minimum_required(VERSION 3.23)
project(AudioVisualizer_FFT)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS system window graphics) # para SFML

add_executable(AudioVisualizer_FFT main.cpp Application.cpp Application.h AudioVisualizer.cpp AudioVisualizer.h)
target_link_libraries(AudioVisualizer_FFT sfml-system sfml-window sfml-graphics  sfml-audio) # para SFML
