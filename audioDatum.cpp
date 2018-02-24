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
