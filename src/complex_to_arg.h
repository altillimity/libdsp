#pragma once
#include <complex>

namespace libdsp
{
    class ComplexToArg
    {
    public:
        size_t work(std::complex<float> *in, size_t length, float *out);
    };
} // namespace libdsp