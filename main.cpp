#include <vector>
#include <iostream>
#include "fileReader.hpp"
#include "fileWriter.hpp"
//#include "audioDatumFourier.hpp"
#include "audioDatum.hpp"
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
  std::vector<float> filter_data = filter.lowpass_filter(100, datum->getSampleRate(), 50);
 
//  for (int i = 0; i < filter_data.size(); i++)
//  {
//    printf("filter sample %i: %e\n", i, filter_data.at(i));
//  }
//  return 0;

  datum->applyImpulseResponse(filter_data);

	fileWriter writer(argv[2]);
	writer.setInput(datum);
	writer.Write();

}
