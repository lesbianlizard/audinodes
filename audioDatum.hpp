#ifndef AUDIODATUM_HPP
#define AUDIODATUM_HPP

class audioDatum {
	public: 
		unsigned int samples;
		unsigned int samplerate;
		int channels;
		float** data; //array of channels, where each channel is an array of samples (floats)

		audioDatum(void);
		~audioDatum(void);

		audioDatum(const unsigned int samples);


		void setLength(const unsigned int samples);
		float* getInterleavedData(void);
};

#endif
