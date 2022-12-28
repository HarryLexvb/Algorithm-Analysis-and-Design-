//
// Created by HarryLex on 20/06/2022.
//

#ifndef SPECTROGRAM_FFT_FFT_H
#define SPECTROGRAM_FFT_FFT_H


#include <complex>
#include <valarray>

const double PI = 3.1415192653589793238460;


typedef std::complex<double> ComplexVal; //short-hand for complex<double> representing a+bi
typedef std::valarray<ComplexVal> SampleArray; //array of complex-valued samples

class CooleyTukey_algorithm
{
public:
    CooleyTukey_algorithm();
    CooleyTukey_algorithm(std::string const& _filePath, int const& _slicingSize);

    void FFT_t(SampleArray &values); //in-place fft
    void iFFT_f(SampleArray &fft); //in-place inverse fft
    std::string* getPathOfSource();
    int getFFTSize();

private:
    std::string path;
    int FFTSize;
};


#endif //SPECTROGRAM_FFT_FFT_H
