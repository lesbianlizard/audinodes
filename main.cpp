#include <vector>
#include <iostream>
#include "fileReader.hpp"
#include "fileWriter.hpp"
#include "audioDatumFourier.hpp"

int main(int argc, char* argv[]) {

//	fileReader reader(argv[1]);
//	reader.execute(); //TODO: perform node execution automatically as needed

  std::cout << "instantiating audioDatumFourier" << std::endl;
  audioDatumFourier fourier(50);
  audioDatum* datum = fourier.getTimeDomainSignal(100);
 // audioDatum* datum = reader.getOutput();
  //datum->print_debug();

	fileWriter writer(argv[2]);
	writer.setInput(datum);
	writer.Write();

}
