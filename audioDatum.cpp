#include "audioDatum.hpp"
#include <vector>
#include <iostream>
#include <string>


audioDatum operator+(const audioDatum& datum1, const audioDatum& datum2)
{
  audioDatum newdatum;
}

void audioDatum::setLength(const unsigned int samples) {
  printf("setting channels: %i\n", this->channels);
  this->samples = samples;

  //	this->data = new float* [this->channels];

  for (int i=0; i<this->channels; i++) {
    printf("setting track %i samples: %i\n", i, samples);
    //this->data[i] = new float[samples];
    std::vector<float> samples_tmp(samples, 0);
    this->data.push_back(samples_tmp);
  }
}

audioDatum::audioDatum(const audioDatum& datum)
{
  this->samples = datum.getSamples();
  this->samplerate = datum.getSampleRate();
  this->channels = datum.getChannels();

  this->setLength(this->samples);

  for (int c = 0; c < this->channels; c++)
  {
    for (int s = 0; s < this->samples; s++)
    {
      this->data[c][s] = datum.getSample(c, s);
    }
  }
}

float* audioDatum::getInterleavedData() {
  int c = this->channels;
  unsigned int sndsize = this->samples * c;
  float* buf = new float[sndsize];

  for (unsigned int i=0; i<sndsize; i++) {
    buf[i] = this->data[i%c][i/c];
  }
  return buf;
}

void audioDatum::putInterleavedData(const float* buf) {
  int c = this->channels;
  unsigned int sndsize = this->samples * c;

  for (unsigned int i=0; i<sndsize; i++) {
    this->data[i%c][i/c] = buf[i];
  }
}

// call default constructor when constructing with known sample count
// see https://en.wikipedia.org/wiki/C%2B%2B11#Object_construction_improvement
audioDatum::audioDatum(const unsigned int samples) : audioDatum() {
  this->setLength(samples);
}

audioDatum::audioDatum() {
  this->channels = 2;
}

audioDatum::~audioDatum() {
  //	printf("deleting audioDatum\n");
  //	for (int i=0; i<this->channels; i++) {
  //		delete[] this->data[i];
  //	}
  //	delete[] this->data;
}

unsigned int audioDatum::getSamples() const
{
  return this->samples;
}

void audioDatum::setSamples(unsigned int samples)
{
  this->samples = samples;
}

unsigned int audioDatum::getSampleRate() const
{
  return this->samplerate;
}

void audioDatum::setSampleRate(unsigned int samplerate)
{
  this->samplerate = samplerate;
}

int audioDatum::getChannels() const
{
  return this->channels;
}

void audioDatum::setChannels(int channels)
{
  this->channels = channels;
}

std::vector< std::vector<float> > audioDatum::getData()
{
  return this->data;
}

float audioDatum::getSample(int channel, unsigned int sample_idx) const
{
  return this->data[channel][sample_idx];
}

void audioDatum::setSample(int channel, unsigned int sample_idx, float sample)
{
  this->data[channel][sample_idx] = sample;
}

void audioDatum::print_debug() const
{
  std::string fname = "[audioDatum::print_debug]: ";
  std::cout << fname << "samples " << this->samples << std::endl;
  std::cout << fname << "samplerate " << this->samplerate << std::endl;
  std::cout << fname << "channels " << this->channels << std::endl;

  for (int i = 0; i < this->samples; i++)
  {
    for (int j = 0; j < this->channels; j++)
    {
      std::cout << fname << "sample " << i << " channel " << j << ": " << this->data[j][i] << std::endl;
    }
  }
}

void audioDatum::applyImpulseResponse(std::vector<float> impulse_response)
{
  int impulse_length = impulse_response.size();
  std::vector< std::vector<float> > data_tmp = this->data; 
  std::vector< std::vector<int> > conv_err_ct;

  for (int i = 0; i < 5; i++)
  {
    std::vector<int> tmp(2, 0);
    conv_err_ct.push_back(tmp);
  }

  for (int c = 0; c < this->channels; c++)
  { 
    for (int n = 0; n < this->samples; n++)
    {
      this->data.at(c).at(n) = 0;
      //std::cout << "convolving channel " << c << " sample " << n << " of " << this->samples << std::endl;

      // case 0
      if (n < -impulse_length - samples)
      {
        try
        {
          this->data.at(c).at(n) = 0;
          conv_err_ct.at(0).at(0)++;
        }
        catch (...)
        {
          conv_err_ct.at(0).at(1)++;
        }
      }
      // case 1
      else if ((n > -impulse_length - samples - 1) && (n < impulse_length - samples))
      {
        try
        {
          this->data.at(c).at(n) = this->convolve(data_tmp.at(c), impulse_response, n, (-samples - n), (impulse_length));
          conv_err_ct.at(1).at(0)++;
        }
        catch (...)
        {
          conv_err_ct.at(1).at(1)++;
        }
      }
      // case 2
      else if ((n > impulse_length - samples - 1) && (n < -impulse_length))
      {
        try
        {
          this->data.at(c).at(n) = this->convolve(data_tmp.at(c), impulse_response, n, (-impulse_length), (impulse_length));
          conv_err_ct.at(2).at(0)++;
        }
        catch (...)
        {
          conv_err_ct.at(2).at(1)++;
        }
      }
      // case 3
      else if ((n > -impulse_length - 1) && (n < impulse_length))
      {
        try
        {
          this->data.at(c).at(n) = this->convolve(data_tmp.at(c), impulse_response, n, (-impulse_length), (-n));
          conv_err_ct.at(3).at(0)++;
        }
        catch (...)
        {
          conv_err_ct.at(3).at(1)++;
        }
      }
      // case 4
      else
      {
        try
        {
          this->data.at(c).at(n) = 0;
          conv_err_ct.at(4).at(0)++;
        }
        catch (...)
        {
          conv_err_ct.at(4).at(1)++;
        }
      }
    }
  }

  for (int i = 0; i < 5; i++)
  {
    std::cout << "case " <<  i << " hits, misses: " << conv_err_ct.at(i).at(0) << ", " << conv_err_ct.at(i).at(1) << std::endl;
  }
}

float audioDatum::convolve(std::vector<float> input, std::vector<float> impulse_response, int n, int lower, int upper)
{
  float result;

  for (int k = lower; k < upper + 1; k++)
  {
    result += impulse_response.at(n + impulse_response.size()) * input.at(n - k);
  } 

  return result;
}
