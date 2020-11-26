#pragma once

#include <complex>

/* Based on the Costas Loop from GNU Radio (https://github.com/gnuradio/gnuradio) */

namespace libdsp
{
    class QuadratureDemod
    {
    private:
        float d_gain;

    public:
        QuadratureDemod(float gain);
        ~QuadratureDemod();

        void set_gain(float gain) { d_gain = gain; }
        float gain() const { return d_gain; }

        size_t work(std::complex<float> *in, size_t length, float *out);
    };
}; // namespace libdsp