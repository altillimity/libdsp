#pragma once

#include <vector>

namespace libdsp
{
    namespace firgen
    {
        /*!
     * \brief design a Root Cosine FIR Filter (do we need a window?)
     *
     * \param gain            overall gain of filter (typically 1.0)
     * \param sampling_freq   sampling freq (Hz)
     * \param symbol_rate     symbol rate, must be a factor of sample rate
     * \param alpha           excess bandwidth factor
     * \param ntaps           number of taps
     */
        std::vector<float>
        root_raised_cosine(double gain,
                           double sampling_freq,
                           double symbol_rate, // Symbol rate, NOT bitrate (unless BPSK)
                           double alpha,       // Excess Bandwidth Factor
                           int ntaps);
    } // namespace firgen
} // namespace libdsp