#include "fir_filter.h"

namespace libdsp
{
    FIRFilterCC::FIRFilterCC(int decimation, const std::vector<float> &taps)
    {
        d_fir = new fir_filter_cc(decimation, taps);
        d_updated = false;
        decimation_m = decimation;

        const int alignment_multiple = 1 / sizeof(float);
    }

    FIRFilterCC::~FIRFilterCC()
    {
        delete d_fir;
    }

    void FIRFilterCC::set_taps(const std::vector<float> &taps)
    {
        d_fir->set_taps(taps);
        d_updated = true;
    }

    std::vector<float> FIRFilterCC::taps() const
    {
        return d_fir->taps();
    }

    size_t FIRFilterCC::work(std::complex<float> *in, size_t length, std::complex<float> *out)
    {
        tmp_.insert(tmp_.end(), in, &in[length]);

        size_t process_size = tmp_.size() - d_fir->ntaps();

        if (decimation_m == 1)
            d_fir->filterN(out, tmp_.data(), process_size);
        else
            d_fir->filterNdec(out, tmp_.data(), process_size, decimation_m);

        tmp_.erase(tmp_.begin(), tmp_.end() - d_fir->ntaps());

        return process_size / decimation_m;
    }
}