#include <vector>
class impulseResponse
{
  public:
    std::vector<float> lowpass_filter(int bandwidth, int sample_freq, int cutoff);
};
