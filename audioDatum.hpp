#ifndef AUDIODATUM_HPP
#define AUDIODATUM_HPP

#include <vector>

class audioDatum {
	public: //private
		unsigned int samples;
		unsigned int samplerate;
		int channels;
		//float** data; //array of channels, where each channel is an array of samples (floats)
    std::vector<std::vector<float> > data;

		audioDatum(void);
		~audioDatum(void);

		audioDatum(const unsigned int samples);
		void setLength(const unsigned int samples);

//public:
    unsigned int getSamples();
    void setSamples(unsigned int samples);
    unsigned int getSampleRate();
    void setSampleRate(unsigned int samplerate);
    int getChannels();
    void setChannels(int channels);
    std::vector< std::vector<float> > getData(); // is this safe? 
    float getSample(int channel, unsigned int sample_idx);
    void setSample(int channel, unsigned int sample_idx, float sample);
    void print_debug(); 

		float* getInterleavedData(void);
		void putInterleavedData(const float* buf);
};

#endif
