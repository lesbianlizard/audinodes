#ifndef AUDIO_DATUM_FOURIER_HPP
#define AUDIO_DATUM_FOURIER_HPP

#include <complex>
#include "audioDatum.hpp"

class audioDatumFourier
{
  private:
    unsigned int samples;
    unsigned int samplerate;
    std::complex<float>** data;
    int channels;

    std::complex<float> get_fourier_series_coefficient(float* time_samples, int idx);
    float get_inverse_fourier_series_sample(std::complex<float>* fourier_coefficients, int idx);

    void init_data_array(); 
  public:
    audioDatumFourier(audioDatum* datum);
    audioDatumFourier(int samples);
    //storeData(audioDatum datum);
    ~audioDatumFourier();

    audioDatum* getTimeDomainSignal(int repetitions);
};


#endif
