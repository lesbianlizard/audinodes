#ifndef AUDIODATUM_HPP
#define AUDIODATUM_HPP

class audioDatum {
	public: //private
		unsigned int samples;
		unsigned int samplerate;
		int channels;
		float** data; //array of channels, where each channel is an array of samples (floats)

		audioDatum(void);
		audioDatum(const unsigned int samples);
    audioDatum(const audioDatum& datum);
		~audioDatum(void);

		void setLength(const unsigned int samples);

//public:
    unsigned int getSamples() const;
    void setSamples(unsigned int samples);
    unsigned int getSampleRate() const;
    void setSampleRate(unsigned int samplerate);
    int getChannels() const;
    void setChannels(int channels);
    float** getData(); // is this safe?
    float getSample(int channel, unsigned int sample_idx) const;
    void setSample(int channel, unsigned int sample_idx, float sample);
    void print_debug() const; 

		float* getInterleavedData(void);
		void putInterleavedData(const float* buf);

    friend audioDatum operator+(const audioDatum& datum1, const audioDatum& datum2);
};

#endif
