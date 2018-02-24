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
	printf("samples: %i\n", sf_info.frames);
	printf("sample rate: %i\n", sf_info.samplerate);
	printf("channels: %i\n\n", sf_info.channels);

	this->sound.samples = sf_info.frames;
	this->sound.samplerate = sf_info.samplerate;
	// this->sound.channels = sf_info.channels;
	this->sound.setLength(sf_info.frames);

	unsigned int sndsize = sf_info.frames * sf_info.channels;
	float snddata[sndsize];

	sf_count_t samples_read = sf_read_float(file, snddata, sndsize);
	sf_close(file);

	for (unsigned long i=0; i<sf_info.frames; i++) {
		for (int c=0; c<sf_info.channels; c++) { //c++ :O
			this->sound.data[c][i] = snddata[i+c];
		}
	}

	printf("value inside execute: %f\n", this->sound.data[0][0]);

}
