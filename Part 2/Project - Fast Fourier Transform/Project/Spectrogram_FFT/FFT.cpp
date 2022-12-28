//
// Created by HarryLex on 20/06/2022.
//

#include "FFT.h"


CooleyTukey_algorithm::CooleyTukey_algorithm(std::string const& _filePath, int const& _slicingSize){
    path = _filePath;
    FFTSize = _slicingSize;
}

CooleyTukey_algorithm::CooleyTukey_algorithm(){
    path = "";
    FFTSize = NULL;
}

SampleArray* Split(SampleArray& val, int start, int skip){
    SampleArray half;

    return nullptr;
}

//see https://stackoverflow.com/questions/28009590/understanding-the-radix-2-fft-recursive-algorithm
void CooleyTukey_algorithm::FFT_t(SampleArray& values)
{
    const size_t N = values.size();
    if (N <= 1) return;

    //separate the array of values into even and odd indices
    SampleArray evens = values[std::slice(0, N / 2, 2)]; //slice starting at 0, N/2 elements, incr by 2
    SampleArray odds = values[std::slice(1, N / 2, 2)];

    //now call recursively
    FFT_t(evens);
    FFT_t(odds);

    //recombine
    for(size_t i=0; i<N/2;i++)
    {
        ComplexVal index = std::polar(1.0, -2 * PI*i / N) * odds[i];
        values[i] = evens[i] + index;
        values[i + N / 2] = evens[i] - index;
    }
}

std::string* CooleyTukey_algorithm::getPathOfSource()
{
    return &path;
}

int CooleyTukey_algorithm::getFFTSize()
{
    return this->FFTSize;
}


/*Insverse FFT_t */
void CooleyTukey_algorithm::iFFT_f(SampleArray& fft)
{
    fft = fft.apply(std::conj); //take the complex conjugate
    FFT_t(fft); //take the fft
    fft = fft.apply(std::conj); //conjugate again

    //normalize values
    fft /= fft.size();
}

