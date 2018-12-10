#include "impulseResponse.hpp"
#include <vector>
#include <cmath>

std::vector<float> impulseResponse::lowpass_filter(int bandwidth, int sample_freq, int cutoff)
{
  std::vector<float> impulses;

  for (int n = -cutoff; n < cutoff + 1; n++)
  {
    if (n == 0)
    {
      impulses.push_back(bandwidth/(sample_freq * M_PI));
    }
    else
    {
      impulses.push_back(sin(static_cast<float>(bandwidth * n) / sample_freq) / (M_PI * n));
    }
  }

  return impulses;
}
