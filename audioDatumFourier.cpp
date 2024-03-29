#include "audioDatumFourier.hpp"
#include <complex>
#include <math.h>
#include <string>
#include <iostream>
#include "audioDatum.hpp"

using namespace std::complex_literals;


audioDatumFourier::audioDatumFourier(int samples)
{
  std::string fname = "[audioDatumFourier::audioDatumFourier()]: ";
  this->samplerate = 44100;
  this->samples = samples;
  this->channels = 2;

  this->init_data_array();

  for (int i = 0; i < this->channels; i++)
  {
    for (int j = 0; j < this->samples; j++)
    {
      std::cout << fname << "setting sample " << j << std::endl;
      if ((j == this->samples - 1))
      {
        this->data[i][j] = 0.1;
      }
      else
      {
        this->data[i][j] = 0;
      }
    }
  }
}

void audioDatumFourier::init_data_array()
{
  //this->data = new std::complex<float>*[this->channels];

  for (int i = 0; i < this->channels; i++)
  {
    //this->data[i] = new std::complex<float>[this->samples];
    std::vector< std::complex<float> > data_tmp(this->samples, 0);
    this->data.push_back(data_tmp);
  }
}

audioDatumFourier::audioDatumFourier(audioDatum* datum)
{
  std::string fname = "[audioDatumFourier::audioDatumFourier(audioDatum* datum)]: ";
  //float** datum_samples = datum->getData();
  std::vector< std::vector< float > > datum_samples = datum->getData();
  this->samples = datum->getSamples();
  this->channels = datum->getChannels();

  this->init_data_array();

  for (int i = 0; i < this->channels; i++)
  {
    for (unsigned int j = 0; j < this->samples; j++)
    {
      std::cout << fname << "computing fourier coefficient " << j <<  " of " << this->samples <<  std::endl;
      this->data[i][j] = this->get_fourier_series_coefficient(datum_samples[i], j);

    }
  }
}

std::complex<float> audioDatumFourier::get_fourier_series_coefficient(std::vector<float>& time_samples, int idx)
{
  std::complex<float> sum = 0;

  for (int n = 0; n < this->samples; n++)
  {
    sum += static_cast<float>(time_samples[n]) * std::exp(static_cast<std::complex<float> >(1i) * static_cast<float>(idx * 2 * M_PI * n / this->samples));
  }

  return sum;
}

float audioDatumFourier::get_inverse_fourier_series_sample(std::vector<std::complex<float> > fourier_coefficients, int idx)
{
  std::complex<float> sum = 0; 

  for (int k = 0; k < this->samples; k++)
  {
    sum += fourier_coefficients[k] * std::exp(static_cast<std::complex<float> >(1i) * static_cast<float>(k * 2 * M_PI * idx / this->samples));
  }

  return sum.real();
}

audioDatum* audioDatumFourier::getTimeDomainSignal(int repetitions)
{
  std::string fname = "[audioDatumFourier::getTimeDomainSignal]: ";
  std::cout << fname << "begin" << std::endl;
  audioDatum* datum = new audioDatum;  
  datum->setSamples(this->samples*repetitions);
  datum->setSampleRate(this->samplerate);
  datum->setChannels(this->channels);
  datum->setLength(this->samples*repetitions);

  for (int i = 0; i < this->channels; i++)
  {
    for(unsigned int j = 0; j < this->samples; j++)
    {
      //std::cout << fname << "giving time domain sample " << j << " channel " << i << " to audioDatum" << std::endl;
      datum->setSample(i, j, this->get_inverse_fourier_series_sample(this->data[i], j));
    }
  }

  for (int k = 1; k < repetitions; k++)
  {
    for (int i = 0; i < this->channels; i++)
    {
      for(unsigned int j = 0; j < this->samples; j++)
      {
        //std::cout <<fname << "copying time domain sample" << j << " channel " << i << " repetition " << k << std::endl;
        datum->setSample(i, j + this->samples*k, datum->getSample(i, j));
      }
    }
  }

  return datum;
}

audioDatumFourier::~audioDatumFourier()
{
}
