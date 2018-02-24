#include <vector>
#include <iostream>
#include "fileReader.hpp"

int main(int argc, char* argv[]) {

	fileReader reader(argv[1]);
	reader.execute();

	printf("value outside of execute: %f\n", reader.sound.data[0][0]);

}
