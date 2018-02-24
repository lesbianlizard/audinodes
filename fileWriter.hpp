#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <string>
#include "sink.hpp"

class fileWriter : public Sink {
	private:
		std::string filepath;
	public:
		void Write();
		fileWriter(const char* filepath);
};

#endif
