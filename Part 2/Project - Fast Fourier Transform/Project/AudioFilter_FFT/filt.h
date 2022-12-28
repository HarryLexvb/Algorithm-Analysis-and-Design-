//
// Created by HarryLex on 20/06/2022.
//

/*
The filters are designed using the "Fourier series method".
This means that the coefficients of a Fourier series approximation to the frequency response of an ideal filter (LPF, HPF, BPF) are used.
to the frequency response of an ideal filter (LPF, HPF, BPF) are used as filter derivatives.
as filter derivatives. The resulting filters have some ripple
in the passband due to the Gibbs phenomenon; the filters are linear phase.
*/

#ifndef AUDIOFILTER_FFT_FILT_H
#define AUDIOFILTER_FFT_FILT_H

#define ECODE(x) {m_error_flag = x; return;}
#define M_PI 3.141592653589793238460

#define MAX_NUM_FILTER_TAPS 1000
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <string.h>
#include <inttypes.h>

enum filterType {LPF, HPF, BPF};

class Filter{
private:
    filterType m_filt_t;
    int m_num_taps;
    int m_error_flag;
    double m_Fs;
    double m_Fx;
    double m_lambda;
    double *m_taps;
    double *m_sr;
    void designLPF();
    void designHPF();

    // Only needed for the bandpass filter case
    double m_Fu, m_phi;
    void designBPF();

public:
    Filter(filterType filt_t, int num_taps, double Fs, double Fx);
    Filter(filterType filt_t, int num_taps, double Fs, double Fl, double Fu);
    ~Filter( );
    void init();
    double do_sample(double data_sample);
    int get_error_flag(){return m_error_flag;};
    void get_taps( double *taps );
};


// Handles LPF and HPF case
Filter::Filter(filterType filt_t, int num_taps, double Fs, double Fx)
{
    m_error_flag = 0;
    m_filt_t = filt_t;
    m_num_taps = num_taps;
    m_Fs = Fs;
    m_Fx = Fx;
    m_lambda = M_PI * Fx / (Fs / 2);

    if (Fs <= 0) ECODE(-1);
    if (Fx <= 0 || Fx >= Fs / 2) ECODE(-2);
    if (m_num_taps <= 0 || m_num_taps > MAX_NUM_FILTER_TAPS) ECODE(-3);

    m_taps = m_sr = NULL;
    m_taps = (double*)malloc(m_num_taps * sizeof(double));
    m_sr = (double*)malloc(m_num_taps * sizeof(double));
    if (m_taps == NULL || m_sr == NULL) ECODE(-4);

    init();

    if (m_filt_t == LPF) designLPF();
    else if (m_filt_t == HPF) designHPF();
    else ECODE(-5);

    return;
}

// Handles BPF case
Filter::Filter(filterType filt_t, int num_taps, double Fs, double Fl,
               double Fu)
{
    m_error_flag = 0;
    m_filt_t = filt_t;
    m_num_taps = num_taps;
    m_Fs = Fs;
    m_Fx = Fl;
    m_Fu = Fu;
    m_lambda = M_PI * Fl / (Fs / 2);
    m_phi = M_PI * Fu / (Fs / 2);

    if (Fs <= 0) ECODE(-10);
    if (Fl >= Fu) ECODE(-11);
    if (Fl <= 0 || Fl >= Fs / 2) ECODE(-12);
    if (Fu <= 0 || Fu >= Fs / 2) ECODE(-13);
    if (m_num_taps <= 0 || m_num_taps > MAX_NUM_FILTER_TAPS) ECODE(-14);

    m_taps = m_sr = NULL;
    m_taps = (double*)malloc(m_num_taps * sizeof(double));
    m_sr = (double*)malloc(m_num_taps * sizeof(double));
    if (m_taps == NULL || m_sr == NULL) ECODE(-15);

    init();

    if (m_filt_t == BPF) designBPF();
    else ECODE(-16);

    return;
}

Filter::~Filter()
{
    if (m_taps != NULL) free(m_taps);
    if (m_sr != NULL) free(m_sr);
}

void Filter::designLPF()
{
    int n;
    double mm;

    for (n = 0; n < m_num_taps; n++) {
        mm = n - (m_num_taps - 1.0) / 2.0;
        if (mm == 0.0) m_taps[n] = m_lambda / M_PI;
        else m_taps[n] = sin(mm * m_lambda) / (mm * M_PI);
    }

    return;
}

void Filter::designHPF()
{
    int n;
    double mm;

    for (n = 0; n < m_num_taps; n++) {
        mm = n - (m_num_taps - 1.0) / 2.0;
        if (mm == 0.0) m_taps[n] = 1.0 - m_lambda / M_PI;
        else m_taps[n] = -sin(mm * m_lambda) / (mm * M_PI);
    }

    return;
}

void Filter::designBPF()
{
    int n;
    double mm;

    for (n = 0; n < m_num_taps; n++) {
        mm = n - (m_num_taps - 1.0) / 2.0;
        if (mm == 0.0) m_taps[n] = (m_phi - m_lambda) / M_PI;
        else m_taps[n] = (sin(mm * m_phi) - sin(mm * m_lambda)) / (mm * M_PI);
    }

    return;
}

void Filter::get_taps(double* taps)
{
    int i;

    if (m_error_flag != 0) return;

    for (i = 0; i < m_num_taps; i++) taps[i] = m_taps[i];

    return;
}

void Filter::init()
{
    int i;

    if (m_error_flag != 0) return;

    for (i = 0; i < m_num_taps; i++) m_sr[i] = 0;

    return;
}


double Filter::do_sample(double data_sample)
{
    int i;
    double result;

    if (m_error_flag != 0) return(0);

    for (i = m_num_taps - 1; i >= 1; i--) {
        m_sr[i] = m_sr[i - 1];
    }
    m_sr[0] = data_sample;

    result = 0;
    for (i = 0; i < m_num_taps; i++) result += m_sr[i] * m_taps[i];

    return result;
}


#endif //SOLUTION_FILT_H
