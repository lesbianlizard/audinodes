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

	printf("%i\n", sf_info.samplerate);
	printf("%i\n", sf_info.channels);

	sf_close(file);
}
