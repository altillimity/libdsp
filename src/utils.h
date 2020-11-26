#pragma once

#include <complex>

namespace libdsp
{
    float branchless_clip(float x, float clip);
    void fast_cc_multiply(std::complex<float> &out, const std::complex<float> cc1, const std::complex<float> cc2);
    void sincosf(float x, float *sinx, float *cosx);
    std::complex<float> gr_expj(float phase);
    void volk_32fc_32f_dot_prod_32fc_generic(std::complex<float> *result, const std::complex<float> *input, const float *taps, unsigned int num_points);
    void volk_32f_x2_dot_prod_32f_generic(float *result, const float *input, const float *taps, unsigned int num_points);
    void volk_32fc_x2_multiply_conjugate_32fc_generic(std::complex<float> *cVector, const std::complex<float> *aVector, const std::complex<float> *bVector, unsigned int num_points);
} // namespace libdsp