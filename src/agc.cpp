#include "agc.h"

namespace libdsp
{
    AgcCC::AgcCC(float rate, float reference, float gain, float max_gain) : _rate(rate), _reference(reference), _gain(gain), _max_gain(max_gain)
    {
    }

    size_t AgcCC::work(std::complex<float> *in, size_t length, std::complex<float> *out)
    {
        scaleN(out, in, length);
        return length;
    }
} // namespace libdsp