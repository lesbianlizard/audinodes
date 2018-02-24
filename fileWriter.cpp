#include <iostream>
#include <sndfile.h>
#include "fileWriter.hpp"

void fileWriter::Write() {
	SF_INFO sf_info;

	sf_info.frames     = this->input->samples;
	sf_info.samplerate = this->input->samplerate;
	sf_info.channels   = this->input->channels;
	sf_info.format     = SF_FORMAT_FLAC | SF_FORMAT_PCM_24;
	sf_info.sections   = 0;
	sf_info.seekable   = 0;
	// sf_info.format     = SF_FORMAT_FLAC | SF_FORMAT_FLOAT;

	printf("is format ok? %i\n", sf_format_check(&sf_info));

	SNDFILE* file = sf_open(this->filepath.c_str(), SFM_WRITE, &sf_info);

	float* buf = this->input->getInterleavedData();
	sf_writef_float(file, buf, this->input->samples);

	sf_close(file);
	delete[] buf;
}

fileWriter::fileWriter(const char* filepath) {
	if (filepath == nullptr) {
		std::cerr << "we can'tz write fielz to nullptrz" << std::endl;
		exit(EXIT_FAILURE);
	}
	this->filepath = filepath;
}
