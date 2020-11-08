#pragma once

#include "fir_filter_imp.h"

namespace libdsp
{
    class FIRFilterCC
    {
    private:
        fir_filter_cc *d_fir;
        bool d_updated;
        int decimation_m;
        std::vector<std::complex<float>> tmp_;

    public:
        FIRFilterCC(int decimation, const std::vector<float> &taps);

        ~FIRFilterCC();

        void set_taps(const std::vector<float> &taps);
        std::vector<float> taps() const;

        size_t work(std::complex<float> *in, size_t length, std::complex<float> *out);
    };
}