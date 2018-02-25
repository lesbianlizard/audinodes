#include <vector>
#include <iostream>
#include "fileReader.hpp"
#include "fileWriter.hpp"
#include "audioDatumFourier.hpp"

int main(int argc, char* argv[]) {

	fileReader reader(argv[1]);
	reader.execute(); //TODO: perform node execution automatically as needed

  std::cout << "instantiating audioDatumFourier" << std::endl;
  audioDatumFourier fourier(reader.getOutput());
  exit(0);

	fileWriter writer(argv[2]);
	writer.setInput(reader.getOutput());
	writer.Write();

}
