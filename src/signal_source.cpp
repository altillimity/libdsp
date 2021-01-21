#include "signal_source.h"

namespace libdsp
{
    SignalSource::SignalSource(double sampling_freq, waveform_t waveform, double frequency, double ampl, std::complex<float> offset, float phase)
        : d_sampling_freq(sampling_freq),
          d_waveform(waveform),
          d_frequency(frequency),
          d_ampl(ampl),
          d_offset(offset)
    {
        this->set_frequency(frequency);
        this->set_phase(phase);
    }

    SignalSource::~SignalSource()
    {
    }

    void SignalSource::set_sampling_freq(double sampling_freq)
    {
        d_sampling_freq = sampling_freq;
        d_nco.set_freq(2 * M_PI * this->d_frequency / this->d_sampling_freq);
    }

    void SignalSource::set_waveform(waveform_t waveform)
    {
        d_waveform = waveform;
    }

    void SignalSource::set_frequency(double frequency)
    {
        d_frequency = frequency;
        d_nco.set_freq(2 * M_PI * this->d_frequency / this->d_sampling_freq);
    }

    void SignalSource::set_amplitude(double ampl)
    {
        d_ampl = ampl;
    }

    void SignalSource::set_offset(std::complex<float> offset)
    {
        d_offset = offset;
    }

    void SignalSource::set_phase(float phase)
    {
        d_nco.set_phase(phase);
    }

    size_t SignalSource::work(std::complex<float> *out, size_t len)
    {
        std::complex<float> t;

        switch (d_waveform)
        {
        case GR_CONST_WAVE:
            t = (std::complex<float>)d_ampl + d_offset;
            std::fill_n(out, len, t);
            break;

        case GR_SIN_WAVE:
        case GR_COS_WAVE:
            d_nco.sincos(out, len, d_ampl);
            if (d_offset == std::complex<float>(0, 0))
                break;

            for (int i = 0; i < len; i++)
            {
                out[i] += d_offset;
            }
            break;

            /* Implements a real square wave high from -PI to 0.
         * The imaginary square wave leads by 90 deg.
         */
        case GR_SQR_WAVE:
            for (int i = 0; i < len; i++)
            {
                if (d_nco.get_phase() < -1 * M_PI / 2)
                    out[i] = std::complex<float>(d_ampl, 0) + d_offset;
                else if (d_nco.get_phase() < 0)
                    out[i] = std::complex<float>(d_ampl, d_ampl) + d_offset;
                else if (d_nco.get_phase() < M_PI / 2)
                    out[i] = std::complex<float>(0, d_ampl) + d_offset;
                else
                    out[i] = d_offset;
                d_nco.step();
            }
            break;

            /* Implements a real triangle wave rising from -PI to 0 and
         * falling from 0 to PI. The imaginary triangle wave leads by
         * 90 deg.
         */
        case GR_TRI_WAVE:
            for (int i = 0; i < len; i++)
            {
                if (d_nco.get_phase() < -1 * M_PI / 2)
                {
                    out[i] =
                        std::complex<float>(d_ampl * d_nco.get_phase() / M_PI + d_ampl,
                                            -1 * d_ampl * d_nco.get_phase() / M_PI - d_ampl / 2) +
                        d_offset;
                }
                else if (d_nco.get_phase() < 0)
                {
                    out[i] = std::complex<float>(d_ampl * d_nco.get_phase() / M_PI + d_ampl,
                                                 d_ampl * d_nco.get_phase() / M_PI + d_ampl / 2) +
                             d_offset;
                }
                else if (d_nco.get_phase() < M_PI / 2)
                {
                    out[i] = std::complex<float>(-1 * d_ampl * d_nco.get_phase() / M_PI + d_ampl,
                                                 d_ampl * d_nco.get_phase() / M_PI + d_ampl / 2) +
                             d_offset;
                }
                else
                {
                    out[i] = std::complex<float>(-1 * d_ampl * d_nco.get_phase() / M_PI + d_ampl,
                                                 -1 * d_ampl * d_nco.get_phase() / M_PI +
                                                     3 * d_ampl / 2) +
                             d_offset;
                }
                d_nco.step();
            }
            break;

            /* Implements a real saw tooth wave rising from -PI to PI.
         * The imaginary saw tooth wave leads by 90 deg.
         */
        case GR_SAW_WAVE:
            for (int i = 0; i < len; i++)
            {
                if (d_nco.get_phase() < -1 * M_PI / 2)
                {
                    out[i] =
                        std::complex<float>(d_ampl * d_nco.get_phase() / (2 * M_PI) + d_ampl / 2,
                                            d_ampl * d_nco.get_phase() / (2 * M_PI) +
                                                5 * d_ampl / 4) +
                        d_offset;
                }
                else
                {
                    out[i] =
                        std::complex<float>(d_ampl * d_nco.get_phase() / (2 * M_PI) + d_ampl / 2,
                                            d_ampl * d_nco.get_phase() / (2 * M_PI) + d_ampl / 4) +
                        d_offset;
                }
                d_nco.step();
            }
            break;
        default:
            throw std::runtime_error("analog::sig_source: invalid waveform");
        }

        return len;
    }
} // namespace libdsp