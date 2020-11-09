#include <complex>

namespace libdsp
{
    class ComplexToReal
    {
    public:
        size_t work(std::complex<float> *in, size_t length, float *out);
    };
} // namespace libdsp