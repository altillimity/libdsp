#include "quadrature_demod.h"
#include <vector>
#include "utils.h"
#include "math/math.h"

namespace libdsp
{
    QuadratureDemod::QuadratureDemod(float gain) : d_gain(gain)
    {
    }

    QuadratureDemod::~QuadratureDemod()
    {
    }

    size_t QuadratureDemod::work(std::complex<float> *in, size_t length, float *out)
    {
        std::vector<std::complex<float>> tmp(length);
        volk_32fc_x2_multiply_conjugate_32fc_generic(&tmp[0], &in[1], &in[0], length);
        for (int i = 0; i < length; i++)
        {
            out[i] = d_gain * fast_atan2f(imag(tmp[i]), real(tmp[i]));
        }

        return length;
    }
}; // namespace libdsp