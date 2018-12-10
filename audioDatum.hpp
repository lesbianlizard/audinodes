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
		audioDatum(const unsigned int samples);
    audioDatum(const audioDatum& datum);
		~audioDatum(void);

		void setLength(const unsigned int samples);

    float convolve(std::vector<float> input, std::vector<float> impulse_response, int n, int lower, int upper);
    float convolve2(std::vector<float>& impulse_response, std::vector<float>& input, int n);

//public:
    unsigned int getSamples() const;
    void setSamples(unsigned int samples);
    unsigned int getSampleRate() const;
    void setSampleRate(unsigned int samplerate);
    int getChannels() const;
    void setChannels(int channels);
    std::vector< std::vector<float> > getData(); // is this safe? 
    float getSample(int channel, unsigned int sample_idx) const;
    void setSample(int channel, unsigned int sample_idx, float sample);
    void print_debug() const; 

		float* getInterleavedData(void);
		void putInterleavedData(const float* buf);

    void applyImpulseResponse(std::vector<float> impulse_response);
    static void applyImpulseResponseThread(std::vector<float>& data_tmp, std::vector<float>& data, std::vector<float>& impulse_response, int thread, int thread_lower, int thread_upper);

    int getPeriodicIndex(int input, int idx_low, int idx_high);

    friend audioDatum operator+(const audioDatum& datum1, const audioDatum& datum2);
};

#endif
