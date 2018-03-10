#include <vector>
#include <iostream>
#include "fileReader.hpp"
#include "fileWriter.hpp"
#include "audioDatumFourier.hpp"
#include "impulseResponse.hpp"

int main(int argc, char* argv[]) {

	fileReader reader(argv[1]);
	reader.execute(); //TODO: perform node execution automatically as needed

  //std::cout << "instantiating audioDatumFourier" << std::endl;
  //audioDatumFourier fourier(50);
  //audioDatum* datum = fourier.getTimeDomainSignal(100);
  //audioDatum datum2(*datum);
  audioDatum* datum = reader.getOutput();
  //datum->print_debug();

  impulseResponse filter;
  datum->applyImpulseResponse(filter.lowpass_filter(500, datum->getSampleRate(), 2500));

	fileWriter writer(argv[2]);
	writer.setInput(datum);
	writer.Write();

}
