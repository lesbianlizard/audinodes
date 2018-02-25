#include <vector>
#include "audioDatum.hpp"
#include <iostream>
#include <string>

void audioDatum::setLength(const unsigned int samples) {
	printf("setting channels: %i\n", this->channels);
	this->samples = samples;

	this->data = new float* [this->channels];

	for (int i=0; i<this->channels; i++) {
		printf("setting track %i samples: %i\n", i, samples);
		this->data[i] = new float[samples];
	}
}

float* audioDatum::getInterleavedData() {
	unsigned int sndsize = this->samples * this->channels;
	float* buf = new float[sndsize];
	for (unsigned int i=0; i<this->samples; i++) {
		for (int c=0; c<this->channels; c++) { //c++ :O
			buf[i*2+c] = this->data[c][i];
		}
	}
	return buf;
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
	printf("deleting audioDatum\n");
	for (int i=0; i<this->channels; i++) {
		delete[] this->data[i];
	}
	delete[] this->data;
}

unsigned int audioDatum::getSamples()
{
  return this->samples;
}

void audioDatum::setSamples(unsigned int samples)
{
  this->samples = samples;
}

unsigned int audioDatum::getSampleRate()
{
  return this->samplerate;
}

void audioDatum::setSampleRate(unsigned int samplerate)
{
  this->samplerate = samplerate;
}

int audioDatum::getChannels()
{
  return this->channels;
}

void audioDatum::setChannels(int channels)
{
  this->channels = channels;
}

float** audioDatum::getData()
{
  return this->data;
}

float audioDatum::getSample(int channel, unsigned int sample_idx)
{
  return this->data[channel][sample_idx];
}

void audioDatum::setSample(int channel, unsigned int sample_idx, float sample)
{
  this->data[channel][sample_idx] = sample;
}

void audioDatum::print_debug()
{
  std::string fname = "[audioDatum::print_debug]: ";
  std::cout << fname << "samples " << this->samples << std::endl;
  std::cout << fname << "samplerate " << this->samplerate << std::endl;
  std::cout << fname << "channels " << this->channels << std::endl;
}
