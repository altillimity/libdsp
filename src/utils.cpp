#include "utils.h"

namespace libdsp
{
    float branchless_clip(float x, float clip)
    {
        return 0.5 * (std::abs(x + clip) - std::abs(x - clip));
    }

    void fast_cc_multiply(std::complex<float> &out, const std::complex<float> cc1, const std::complex<float> cc2)
    {
        // The built-in complex.h multiply has significant NaN/INF checking that
        // considerably slows down performance.  While on some compilers the
        // -fcx-limit-range flag can be used, this fast function makes the math consistent
        // in terms of performance for the Costas loop.
        float o_r, o_i;

        o_r = (cc1.real() * cc2.real()) - (cc1.imag() * cc2.imag());
        o_i = (cc1.real() * cc2.imag()) + (cc1.imag() * cc2.real());

        out.real(o_r);
        out.imag(o_i);
    }

    void sincosf(float x, float *sinx, float *cosx)
    {
        *sinx = ::sinf(x);
        *cosx = ::cosf(x);
    }

    std::complex<float> gr_expj(float phase)
    {
        float t_imag, t_real;
        sincosf(phase, &t_imag, &t_real);
        return std::complex<float>(t_real, t_imag);
    }

    void volk_32fc_32f_dot_prod_32fc_generic(std::complex<float> *result, const std::complex<float> *input, const float *taps, unsigned int num_points)
    {

        float res[2];
        float *realpt = &res[0], *imagpt = &res[1];
        const float *aPtr = (float *)input;
        const float *bPtr = taps;
        unsigned int number = 0;

        *realpt = 0;
        *imagpt = 0;

        for (number = 0; number < num_points; number++)
        {
            *realpt += ((*aPtr++) * (*bPtr));
            *imagpt += ((*aPtr++) * (*bPtr++));
        }

        *result = *(std::complex<float> *)(&res[0]);
    }

    void volk_32f_x2_dot_prod_32f_generic(float *result, const float *input, const float *taps, unsigned int num_points)
    {

        float dotProduct = 0;
        const float *aPtr = input;
        const float *bPtr = taps;
        unsigned int number = 0;

        for (number = 0; number < num_points; number++)
        {
            dotProduct += ((*aPtr++) * (*bPtr++));
        }

        *result = dotProduct;
    }

    void volk_32fc_x2_multiply_conjugate_32fc_generic(std::complex<float> *cVector, const std::complex<float> *aVector, const std::complex<float> *bVector, unsigned int num_points)
    {
        std::complex<float> *cPtr = cVector;
        const std::complex<float> *aPtr = aVector;
        const std::complex<float> *bPtr = bVector;
        unsigned int number = 0;

        for (number = 0; number < num_points; number++)
        {
            *cPtr++ = (*aPtr++) * conj(*bPtr++);
        }
    }
} // namespace libdsp