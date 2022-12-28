//
// Created by HarryLex on 20/06/2022.
//

#ifndef AUDIOANALYSER_FFT_ANALYSER_H
#define AUDIOANALYSER_FFT_ANALYSER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class analyser{
private:
    //Functions
    void mergechannel();

    //Data members

    //Original
    sf::SoundBuffer origbuffer;
    const sf::Int16* origsamples;
    unsigned int origchannelcount;
    unsigned int origsamplerate;
    sf::Uint64 origsamplecount;

    //Mono
    sf::SoundBuffer monobuffer;
    std::vector<sf::Int16> monosamples;
    unsigned int monosamplerate;

    //Mapped
    std::vector<sf::Int16> mappedSample;

public:
    analyser(std::string filename);

    sf::Sound sound;
    sf::Time duration;


    void mapBuffer(int high, int low);

    int getHeight();
};

#endif //AUDIOANALYSER_FFT_ANALYSER_H
