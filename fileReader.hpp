#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>
#include "audioDatum.hpp"
#include "source.hpp"

class fileReader : public Source {
	protected:
		std::string filepath;

	public:
		audioDatum sound;//TODO: protected, public for testing
		fileReader(const char* filepath);
		void execute(void);

};

#endif
