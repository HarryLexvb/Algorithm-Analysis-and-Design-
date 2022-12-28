//
// Created by HarryLex on 20/06/2022.
//

#include "analyser.h"

analyser::analyser(std::string filename){
    if(!origbuffer.loadFromFile(filename))
        throw "Failed to open file!";

    //Load Details
    origchannelcount = origbuffer.getChannelCount();
    duration = origbuffer.getDuration();
    origsamplecount = origbuffer.getSampleCount();
    origsamplerate = origbuffer.getSampleRate();
    origsamples = origbuffer.getSamples();

    mergechannel();
}

void analyser::mergechannel(){
    if (origchannelcount==1) return;

    for (int i=0; i<origsamplecount; i+=2)
        monosamples.push_back((origsamples[i]+origsamples[i+1])/2);

    monobuffer.loadFromSamples(&monosamples[0], origsamplecount/2, 1, origsamplerate );

    sound.setBuffer(monobuffer);
}


void analyser::mapBuffer(int high, int low){
    mappedSample.clear();

    int new_range = high - low;

    for (int i=0; i<origsamplecount/2; i++)
        mappedSample.push_back(low + ((monosamples[i]+32768)*new_range/65535));
}

int analyser::getHeight(){
    int val = mappedSample[sound.getPlayingOffset().asSeconds()*origsamplerate];
    return val;
}