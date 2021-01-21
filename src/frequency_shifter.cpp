#include "frequency_shifter.h"
#include "utils.h"

namespace libdsp
{
    FrequencyShifter::FrequencyShifter(double samplerate, double shift, int work_size) : d_shift(shift), d_samplerate(samplerate), d_signal_source(SignalSource(samplerate, GR_SIN_WAVE, shift, 1))
    {
        signalBuffer = new std::complex<float>[work_size];
    }

    FrequencyShifter::~FrequencyShifter()
    {
        delete[] signalBuffer;
    }

    size_t FrequencyShifter::work(std::complex<float> *in, size_t length, std::complex<float> *out)
    {
        d_signal_source.work(signalBuffer, length);

        for (int i = 0; i < length; i++)
            fast_cc_multiply(out[i], signalBuffer[i], in[i]);

        return length;
    }

    double FrequencyShifter::getShift()
    {
        return d_shift;
    }

    void FrequencyShifter::setShift(double shift)
    {
        d_shift = shift;
        d_signal_source.set_frequency(shift);
    }
} // namespace libdsp