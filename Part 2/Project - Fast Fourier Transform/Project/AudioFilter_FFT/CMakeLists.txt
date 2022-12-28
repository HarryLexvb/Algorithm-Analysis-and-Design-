cmake_minimum_required(VERSION 3.23)
project(AudioFilter_FFT)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS system window graphics) # para SFML


add_executable(AudioFilter_FFT main.cpp FFT.h filt.h)
target_link_libraries(AudioFilter_FFT sfml-system sfml-window sfml-graphics  sfml-audio) # para SFML