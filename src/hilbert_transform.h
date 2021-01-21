#pragma once
#include "fir_filter_imp.h"
#include "fft_window.h"

namespace libdsp
{
    class HilbertTransform
    {
    private:
        unsigned int d_ntaps;
        fir_filter_fff d_hilb;
        std::vector<float> tmp_;

    public:
        HilbertTransform(unsigned int ntaps, fft::window::win_type window = fft::window::WIN_HAMMING, double beta = 6.76);
        ~HilbertTransform();

        size_t work(float *in, size_t length, std::complex<float> *out);
    };
} // namespace libdsp