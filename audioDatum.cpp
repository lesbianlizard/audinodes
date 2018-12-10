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


  for (int c = 0; c < this->channels; c++)
  { 
    printf("convolving channel c=%i\n", c);

    for (int n = 0; n < this->samples; n++)
    {
      this->data.at(c).at(n) = this->convolve(data_tmp.at(c), impulse_response, n, -impulse_length + 1 , impulse_length - 1);

      if (n%1000 == 0)
      {
        printf("convolving channel %i sample n=%i\n", c, n);
        printf("old sample %i = %f\n", n, data_tmp.at(c).at(n));
        printf("new sample %i = %f\n", n, this->data.at(c).at(n));
      }

    }
    printf("done convolving channel c=%i\n", c);
  }

}

int audioDatum::getPeriodicIndex(int input, int idx_low, int idx_high)
{
  if ((input >= idx_low) && (input <= idx_high))
  {
    return input;
  }
  else if (input < idx_low)
  {
    return this->getPeriodicIndex(idx_high - (idx_low - input), idx_low, idx_high);
  }
  else if (input > idx_high)
  {
    return this->getPeriodicIndex(idx_low + (input - idx_high), idx_low, idx_high);
  }
}

float audioDatum::convolve(std::vector<float> input, std::vector<float> impulse_response, int n, int lower, int upper)
{
//  printf("audioDatum::convolve start\n");
  //printf("lower: %i, upper: %i\n", lower, upper);
  float result=0;

  for (int i = lower; i < upper + 1; i++)
  {
    //printf("convolving sum i=%i, n=%i\n", i, n);
    //printf("result += impulse_response.at(%i) * input.at(%i)\n", this->getPeriodicIndex(n - i, 0, upper), this->getPeriodicIndex(i, 0, this->samples));
    result += impulse_response.at(this->getPeriodicIndex(n - i, 0, upper)) * input.at(this->getPeriodicIndex(i, 0, this->samples));
//    printf("factor 1: %e\n", impulse_response.at(this->getPeriodicIndex(n - i, 0, upper))); 
//    printf("factor 2: %e\n", input.at(this->getPeriodicIndex(i, 0, this->samples)));
//    printf("convolution result: %e\n", result);
  } 

  return result;
}
