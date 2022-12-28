//
// Created by HarryLex on 20/06/2022.
//

#ifndef AUDIOVISUALIZER_FFT_APPLICATION_H
#define AUDIOVISUALIZER_FFT_APPLICATION_H



#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "AudioVisualizer.h"

class Application {
private:
    const std::string _title{"SFML Audio Visualizer"};

    sf::RenderWindow _window;
    sf::Event _event{};
    sf::Sound _music{};
    sf::SoundBuffer _soundBuffer{};

    sf::CircleShape _tmpCircle{};

    double _deltaTime{0};
    size_t _framerate{0};
    std::unique_ptr<AudioVisualizer> _visualizer{nullptr};

    void _pollEvents();
    void _update();
    void _render();
    void _updateFramerate();
public:
    Application();

    void run();
};


#endif //AUDIOVISUALIZER_FFT_APPLICATION_H
