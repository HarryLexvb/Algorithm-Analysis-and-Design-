cmake_minimum_required(VERSION 3.23)
project(AudioAnalyser_FFT)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS system window graphics) # para SFML

add_executable(AudioAnalyser_FFT main.cpp analyser.h analyser.cpp)
target_link_libraries(AudioAnalyser_FFT sfml-system sfml-window sfml-graphics  sfml-audio) # para SFML
