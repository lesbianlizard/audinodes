#include "impulseResponse.hpp"
#include <vector>
#include <cmath>

std::vector<float> impulseResponse::lowpass_filter(int bandwidth, int sample_freq, int cutoff)
{
  std::vector<float> impulses;

  for (int n = -cutoff; n < cutoff + 1; n++)
  {
   impulses.push_back(sin(static_cast<float>(bandwidth * n) / sample_freq) / (M_PI * 10));
  }

  return impulses;
}
