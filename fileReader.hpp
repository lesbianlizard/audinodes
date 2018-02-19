#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>
#include "source.hpp"

class fileReader : public Source {
	protected:
		std::string filepath;
		// char* filepath;

	public:
		fileReader(const char* filepath);
		// ~fileReader(void);
		void execute(void);

};

#endif
