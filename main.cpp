#include <vector>
#include <iostream>
#include "fileReader.hpp"

int main(int argc, char* argv[]) {

	fileReader reader(argv[1]);
	reader.execute();
	exit(EXIT_SUCCESS);

}
