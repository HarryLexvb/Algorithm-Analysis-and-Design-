//
// Created by HarryLex on 20/06/2022.
//

#include "AudioVisualizer.h"

void AudioVisualizer::_smoothArray(decltype(_scaleList) &data)
{
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it == data.begin())
            *it = (*it + *(it + 1)) / 2.0;
        else if (it == (data.end() - 1))
            *it = (*it + *(it - 1)) / 2.0;
        else
            *it = (*(it - 1) + *it + *(it + 1)) / 3.0;
    }
}

AudioVisualizer::AudioVisualizer(decltype(_sound) sound, decltype(_buffer) buffer)
        : _sound{sound}, _buffer{buffer},
          _bufferData{_buffer.getChannelCount(), _buffer.getSampleCount(),
                      _buffer.getSampleRate() * _buffer.getChannelCount()}
{
    _array.resize(BUFFER_SIZE);
}

void AudioVisualizer::_fastFourierTransform(decltype(_array) &array)
{
    const auto size = array.size();

    if (size < 2)
        return;

    auto even = decltype(_array)(array[std::slice(0, size / 2, 2)]);
    auto odd = decltype(_array)(array[std::slice(1, size / 2, 2)]);

    _fastFourierTransform(even);
    _fastFourierTransform(odd);

    for (decltype(array.size()) i = 0; i < size / 2; ++i) {
        Complex comp = std::polar(1.0, -2 * M_PI * i / size) * odd[i];
        array[i] = even[i] + comp;
        array[i + size / 2] = even[i] - comp;
    }
}

AudioVisualizer::VisualizationData AudioVisualizer::getVisualizationData()
{
    const auto position = static_cast<size_t>(_sound.getPlayingOffset().asSeconds() * _bufferData.sampleRate);

    for (auto i = position; i - position < BUFFER_SIZE && i < _bufferData.sampleCount; ++i)
        _array[i - position] = Complex(_buffer.getSamples()[i], 0.0);

    _fastFourierTransform(_array);

    double sum = 0;
    size_t index = 0;
    for (auto &value : _array) {
        const auto abs = std::abs(value) / FREQ_MAX;

        sum += abs;
        _scaleList[index++] = abs;
    }

    _smoothArray(_scaleList);
    return VisualizationData{sum / _array.size(), &_scaleList};
}
