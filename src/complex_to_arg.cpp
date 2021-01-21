#include "complex_to_arg.h"

namespace libdsp
{
    size_t ComplexToArg::work(std::complex<float> *in, size_t length, float *out)
    {
        // The fast_atan2f is faster than Volk
        for (int i = 0; i < length; i++)
        {
            out[i] = std::arg(in[i]);
            //out[i] = atan2f(in[i]);
        }

        return length;
    }
} // namespace libdsp