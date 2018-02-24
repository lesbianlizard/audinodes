#include <vector>
#include "audioDatum.hpp"
#include <iostream>

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
	fprintf(stderr, "constructing audiodatum\n");
	this->channels = 2;
}

audioDatum::~audioDatum() {
	printf("deleting audioDatum\n");
	for (int i=0; i<this->channels; i++) {
		delete[] this->data[i];
	}
	delete[] this->data;
}
