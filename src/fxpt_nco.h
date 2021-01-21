#pragma once

#include <complex>
#include "fxpt.h"

namespace libdsp
{
    class fxpt_nco
    {
        uint32_t d_phase;
        int32_t d_phase_inc;

    public:
        fxpt_nco() : d_phase(0), d_phase_inc(0) {}

        ~fxpt_nco() {}

        // radians
        void set_phase(float angle) { d_phase = fxpt::float_to_fixed(angle); }

        void adjust_phase(float delta_phase)
        {
            d_phase += fxpt::float_to_fixed(delta_phase);
        }

        // angle_rate is in radians / step
        void set_freq(float angle_rate)
        {
            d_phase_inc = fxpt::float_to_fixed(angle_rate);
        }

        // angle_rate is a delta in radians / step
        void adjust_freq(float delta_angle_rate)
        {
            d_phase_inc += fxpt::float_to_fixed(delta_angle_rate);
        }

        // increment current phase angle

        void step() { d_phase += d_phase_inc; }

        void step(int n) { d_phase += d_phase_inc * n; }

        // units are radians / step
        float get_phase() const { return fxpt::fixed_to_float(d_phase); }
        float get_freq() const { return fxpt::fixed_to_float(d_phase_inc); }

        // compute sin and cos for current phase angle
        void sincos(float *sinx, float *cosx) const
        {
            *sinx = fxpt::sin(d_phase);
            *cosx = fxpt::cos(d_phase);
        }

        // compute cos and sin for a block of phase angles
        void sincos(std::complex<float> *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] =
                    std::complex<float>(fxpt::cos(d_phase) * ampl, fxpt::sin(d_phase) * ampl);
                step();
            }
        }

        // compute sin for a block of phase angles
        void sin(float *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (float)(fxpt::sin(d_phase) * ampl);
                step();
            }
        }

        // compute cos for a block of phase angles
        void cos(float *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (float)(fxpt::cos(d_phase) * ampl);
                step();
            }
        }

        // compute sin for a block of phase angles
        void sin(std::int8_t *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (std::int8_t)(fxpt::sin(d_phase) * ampl);
                step();
            }
        }

        // compute cos for a block of phase angles
        void cos(std::int8_t *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (std::int8_t)(fxpt::cos(d_phase) * ampl);
                step();
            }
        }

        // compute sin for a block of phase angles
        void sin(short *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (short)(fxpt::sin(d_phase) * ampl);
                step();
            }
        }

        // compute cos for a block of phase angles
        void cos(short *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (short)(fxpt::cos(d_phase) * ampl);
                step();
            }
        }

        // compute sin for a block of phase angles
        void sin(int *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (int)(fxpt::sin(d_phase) * ampl);
                step();
            }
        }

        // compute cos for a block of phase angles
        void cos(int *output, int noutput_items, double ampl = 1.0)
        {
            for (int i = 0; i < noutput_items; i++)
            {
                output[i] = (int)(fxpt::cos(d_phase) * ampl);
                step();
            }
        }

        // compute cos or sin for current phase angle
        float cos() const { return fxpt::cos(d_phase); }
        float sin() const { return fxpt::sin(d_phase); }
    };
}; // namespace libdsp