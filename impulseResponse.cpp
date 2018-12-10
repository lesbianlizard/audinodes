#include "impulseResponse.hpp"
#include <vector>
#include <cmath>

std::vector<float> impulseResponse::bandpass_filter(float cutoff_freq_low, float cutoff_freq_high, int sample_freq, int cutoff_samples)
{
  std::vector<float> impulses;

  for (int n = -cutoff_samples; n < cutoff_samples + 1; n++)
  {
    if (n == 0)
    {
      impulses.push_back((cutoff_freq_high - cutoff_freq_low)/(sample_freq * M_PI));
    }
    else
    {
      impulses.push_back((sin((cutoff_freq_high * n) / sample_freq) - sin((cutoff_freq_low * n) / sample_freq) ) / (M_PI * n));
    }
  }

  return impulses;
}

std::vector<float> impulseResponse::highpass_filter(float cutoff_freq_low, int sample_freq, int cutoff_samples)
{
  return this->bandpass_filter(cutoff_freq_low, sample_freq*M_PI, sample_freq, cutoff_samples);
}

std::vector<float> impulseResponse::lowpass_filter(float cutoff_freq_high, int sample_freq, int cutoff_samples)
{
  return this->bandpass_filter(0, cutoff_freq_high, sample_freq, cutoff_samples);
}
