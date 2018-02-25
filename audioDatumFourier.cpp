#include "audioDatumFourier.hpp"
#include <complex>
#include <math.h>
#include <string>
#include <iostream>


audioDatumFourier::audioDatumFourier()
{
  this->samples = 0;
  this->channels = 0;
}

audioDatumFourier::audioDatumFourier(audioDatum* datum)
{
  std::string fname = "[audioDatumFourier::audioDatumFourier]: ";
  float** datum_samples = datum->getData();
  this->samples = datum->getSamples();
  this->channels = datum->getChannels();

  this->data = new std::complex<float>*[this->channels];

  for (int i = 0; i < this->channels; i++)
  {
    this->data[i] = new std::complex<float>[this->samples];
  }

  for (int i = 0; i < this->channels; i++)
  {
    for (unsigned int j = 0; j < this->samples; j++)
    {
      std::cout << fname << "computing fourier coefficient " << j <<  " of " << this->samples <<  std::endl;
      this->data[i][j] = this->get_fourier_series_coefficient(datum_samples[i], j);

    }
  }
}

std::complex<float> audioDatumFourier::get_fourier_series_coefficient(float* time_samples, int idx)
{
  std::complex<float> sum = 0;

  for (int n = 0; n < this->samples; n++)
  {
    sum += time_samples[n] * std::exp(static_cast<std::complex<float> >(1i * idx * 2 * M_PI * n / this->samples));
  }
}

float audioDatumFourier::get_inverse_fourier_series_sample(std::complex<float>* fourier_coefficients, int idx)
{
  std::complex<float> sum = 0; 

  for (int k = 0; k < this->samples; k++)
  {
    sum += fourier_coefficients[k] * std::exp(static_cast<std::complex<float> >(1i * k * 2 * M_PI * idx / this->samples));
  }

  return sum.real();
}

audioDatum audioDatumFourier::getTimeDomainSignal()
{
  audioDatum datum;  
  datum.setSamples(this->samples);
  datum.setSampleRate(this->samplerate);
  datum.setChannels(this->channels);
  datum.setLength(this->samples);

  for (int i = 0; i < this->channels; i++)
  {
    for(unsigned int j = 0; j < this->samples; j++)
    {
      datum.setSample(i, j, this->get_inverse_fourier_series_sample(this->data[i], j));
    }
  }
}
