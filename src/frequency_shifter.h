#pragma once
#include "signal_source.h"

namespace libdsp
{
    class FrequencyShifter
    {
    private:
        SignalSource d_signal_source;
        double d_shift;
        double d_samplerate;
        std::complex<float> *signalBuffer;

    public:
        FrequencyShifter(double samplerate, double shift, int work_size = 8192);
        ~FrequencyShifter();
        size_t work(std::complex<float> *in, size_t length, std::complex<float> *out);

        double getShift();
        void setShift(double shift);
    };
} // namespace libdsp