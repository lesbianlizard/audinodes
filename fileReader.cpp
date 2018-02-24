#include <iostream>
#include <sndfile.h>
#include "fileReader.hpp"

fileReader::fileReader(const char* filepath) {
	// TODO: add proper exceptions
	if (filepath == nullptr) {
		std::cout << "no. can't make fileReader without file. bad." << std::endl;
		exit(EXIT_FAILURE);
	}
	this->filepath = filepath;
};

void fileReader::execute() {
	SF_INFO sf_info;
	SNDFILE* file = sf_open(this->filepath.c_str(), SFM_READ, &sf_info);

	if (file == nullptr) {
		std::cout << ":( sndfile didn't read the file " << this->filepath << std::endl;
		exit(EXIT_FAILURE);
	}

	//debug
	printf("\n read file '%s':\n", this->filepath.c_str());
	printf("samples: %li\n", sf_info.frames);
	printf("sample rate: %i\n", sf_info.samplerate);
	printf("channels: %i\n\n", sf_info.channels);

	this->sound.samples = sf_info.frames;
	this->sound.samplerate = sf_info.samplerate;
	this->sound.channels = sf_info.channels;
	this->sound.setLength(sf_info.frames);

	unsigned int sndsize = sf_info.frames * sf_info.channels;

	float* sndbuf = new float[sndsize];
	sf_read_float(file, sndbuf, sndsize);
	this->sound.putInterleavedData(sndbuf);

	delete[] sndbuf;
	sf_close(file);

	printf("value inside execute: %f\n", this->sound.data[0][0]);

}
