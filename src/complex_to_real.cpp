#include "complex_to_real.h"

namespace libdsp
{
    size_t ComplexToReal::work(std::complex<float> *in, size_t length, float *out)
    {
        for (int i = 0; i < length; i++)
            out[i] = in[i].real();

        return length;
    }
} // namespace libdsp