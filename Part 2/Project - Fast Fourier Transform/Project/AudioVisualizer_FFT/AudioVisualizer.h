//
// Created by HarryLex on 20/06/2022.
//

#ifndef AUDIOVISUALIZER_FFT_AUDIOVISUALIZER_H
#define AUDIOVISUALIZER_FFT_AUDIOVISUALIZER_H


#pragma once

// For Windows
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstddef>
#include <complex>
#include <array>
#include <valarray>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class AudioVisualizer final {
public:
    static constexpr size_t BUFFER_SIZE{8196};
    static constexpr double FREQ_MAX{62500};
private:
    using Complex = std::complex<double>;
    using ComplexArray = std::valarray<Complex>;

    const sf::Sound &_sound;
    const sf::SoundBuffer &_buffer;

    ComplexArray _array{};
    std::array<double, BUFFER_SIZE> _scaleList{};

    struct SoundBufferData {
        decltype(_buffer.getChannelCount()) channelCount;
        decltype(_buffer.getSampleCount()) sampleCount;
        decltype(_buffer.getSampleRate()) sampleRate;

        SoundBufferData(decltype(_buffer.getChannelCount()) channelCount,
                        decltype(_buffer.getSampleCount()) sampleCount,
                        decltype(_buffer.getSampleRate()) sampleRate)
                : channelCount{channelCount}, sampleCount{sampleCount}, sampleRate{sampleRate}
        {}
    };

    struct VisualizationData {
        const double scaleAverage{0};
        const decltype(_scaleList) *scaleList{};
    };

    const SoundBufferData _bufferData;

    void _fastFourierTransform(decltype(_array) &array);

    static void _smoothArray(decltype(_scaleList) &data);

public:
    AudioVisualizer(decltype(_sound) sound, decltype(_buffer) buffer);

    AudioVisualizer(const AudioVisualizer &) = delete;
    AudioVisualizer &operator=(const AudioVisualizer &) = delete;

    VisualizationData getVisualizationData();
};



#endif //AUDIOVISUALIZER_FFT_AUDIOVISUALIZER_H
