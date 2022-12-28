cmake_minimum_required(VERSION 3.23)
project(Spectrogram_FFT)

set(CMAKE_CXX_STANDARD 23)
find_package(SFML 2.5 COMPONENTS system window graphics) # para SFML

add_executable(Spectrogram_FFT main.cpp FFT.cpp FFT.h Spectrogram.cpp Spectrogram.h)

target_link_libraries(Spectrogram_FFT sfml-system sfml-window sfml-graphics  sfml-audio) # para SFML