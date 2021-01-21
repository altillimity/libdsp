#pragma once

#include "fxpt_nco.h"

namespace libdsp
{
    /*!
 * \brief Types of signal generator waveforms.
 * \ingroup waveform_generators_blk
 */
    typedef enum
    {
        GR_CONST_WAVE = 100,
        GR_SIN_WAVE,
        GR_COS_WAVE,
        GR_SQR_WAVE,
        GR_TRI_WAVE,
        GR_SAW_WAVE
    } waveform_t;

    class SignalSource
    {
    private:
        double d_sampling_freq;
        waveform_t d_waveform;
        double d_frequency;
        double d_ampl;
        std::complex<float> d_offset;
        fxpt_nco d_nco;

    public:
        SignalSource(double sampling_freq, waveform_t waveform, double wave_freq, double ampl, std::complex<float> offset = 0, float phase = 0);
        ~SignalSource();

        double sampling_freq() const { return d_sampling_freq; }
        waveform_t waveform() const { return d_waveform; }
        double frequency() const { return d_frequency; }
        double amplitude() const { return d_ampl; }
        std::complex<float> offset() const { return d_offset; }
        float phase() const { return d_nco.get_phase(); }

        void set_sampling_freq(double sampling_freq);
        void set_waveform(waveform_t waveform);

        void set_frequency(double frequency);
        void set_amplitude(double ampl);
        void set_offset(std::complex<float> offset);
        void set_phase(float phase);

        size_t work(float *out, size_t len);
        size_t work(std::complex<float> *out, size_t len);
    };
} // namespace libdsp