#include <vector>
#include <iostream>
#include "fileReader.hpp"
#include "fileWriter.hpp"

int main(int argc, char* argv[]) {

	fileReader reader(argv[1]);
	reader.execute(); //TODO: perform node execution automatically as needed

	fileWriter writer(argv[2]);
	writer.setInput(reader.getOutput());
	writer.Write();

}
