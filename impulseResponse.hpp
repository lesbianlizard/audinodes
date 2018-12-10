#include <vector>
class impulseResponse
{
  public:
    std::vector<float> bandpass_filter(float cutoff_freq_low, float cutoff_freq_high, int sample_freq, int cutoff_samples);
    std::vector<float> lowpass_filter(float cutoff_freq_high, int sample_freq, int cutoff_samples);
    std::vector<float> highpass_filter(float cutoff_freq_low, int sample_freq, int cutoff_samples);
};
