#include "carrier_pll_psk.h"
#include "utils.h"

#define M_TWOPI (2 * M_PI)

namespace libdsp
{
    float phase_wrap(float phase)
    {
        while (phase < -M_PI)
            phase += M_TWOPI;
        while (phase > M_PI)
            phase -= M_TWOPI;

        return phase;
    }

    BPSKCarrierPLL::BPSKCarrierPLL(float alpha, float beta, float max_offset) : d_alpha(alpha),
                                                                                d_beta(beta),
                                                                                d_max_offset(max_offset),
                                                                                d_phase(0.0),
                                                                                d_freq(0.0)
    {
    }

    BPSKCarrierPLL::~BPSKCarrierPLL()
    {
    }

    size_t BPSKCarrierPLL::work(std::complex<float> *in, size_t length, float *out)
    {
        for (int i = 0; i < length; i++)
        {

            // Generate and mix out carrier
            float re, im;
            sincosf(d_phase, &im, &re);
            out[i] = (in[i] * std::complex<float>(re, -im)).imag();

            // Adjust PLL phase/frequency
            float error = phase_wrap(atan2f(in[i].imag(), in[i].real()) - d_phase);
            d_freq = branchless_clip(d_freq + error * d_beta, d_max_offset);
            d_phase = phase_wrap(d_phase + error * d_alpha + d_freq);
        }

        return length;
    }
} // namespace libdsp