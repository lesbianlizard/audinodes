#include "impulseResponse.hpp"
#include <vector>
#include <cmath>

std::vector<float> impulseResponse::lowpass_filter(int bandwidth, int sample_freq, int cutoff)
{
  std::vector<float> impulses;

  for (int n = -cutoff; n < cutoff + 1; n++)
  {
   impulses.push_back(sin(bandwidth * n / sample_freq) / (M_PI * n));
  }

  return impulses;
}
