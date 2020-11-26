#include "rational_resampler.h"

namespace libdsp
{
    RationalResamplerCCF::RationalResamplerCCF(unsigned interpolation, unsigned decimation, const std::vector<float> &taps) : d_history(1),
                                                                                                                              d_decimation(decimation),
                                                                                                                              d_ctr(0),
                                                                                                                              d_updated(false)
    {
        if (interpolation == 0)
            throw std::out_of_range(
                "rational_resampler_base_ccf: interpolation must be > 0");
        if (decimation == 0)
            throw std::out_of_range(
                "rational_resampler_base_ccf: decimation must be > 0");

        d_firs.reserve(interpolation);
        for (unsigned i = 0; i < interpolation; i++)
        {
            d_firs.emplace_back(1, std::vector<float>());
        }

        set_taps(taps);
        install_taps(d_new_taps);
    }

    void RationalResamplerCCF::install_taps(const std::vector<float> &taps)
    {
        int nfilters = this->interpolation();
        int nt = taps.size() / nfilters;

        std::vector<std::vector<float>> xtaps(nfilters);

        for (int n = 0; n < nfilters; n++)
            xtaps[n].resize(nt);

        for (int i = 0; i < (int)taps.size(); i++)
            xtaps[i % nfilters][i / nfilters] = taps[i];

        for (int n = 0; n < nfilters; n++)
            d_firs[n].set_taps(xtaps[n]);

        d_history = nt;
        d_updated = false;
    }

    void RationalResamplerCCF::set_taps(const std::vector<float> &taps)
    {
        d_new_taps = taps;
        d_updated = true;

        // round up length to a multiple of the interpolation factor
        int n = taps.size() % this->interpolation();
        if (n > 0)
        {
            n = this->interpolation() - n;
            while (n-- > 0)
            {
                d_new_taps.insert(d_new_taps.end(), 0);
            }
        }
    }

    std::vector<float> RationalResamplerCCF::taps() const
    {
        return d_new_taps;
    }

    size_t RationalResamplerCCF::work(std::complex<float> *in, size_t length, std::complex<float> *out)
    {
        tmp_.insert(tmp_.end(), in, &in[length]);

        unsigned int ctr = d_ctr;
        int count = 0;

        int i = 0;
        while (count < tmp_.size())
        {
            out[i++] = d_firs[ctr].filter(in);
            ctr += this->decimation();
            while (ctr >= this->interpolation())
            {
                ctr -= this->interpolation();
                in++;
                count++;
            }
        }

        d_ctr = ctr;

        tmp_.erase(tmp_.begin(), tmp_.end() - d_history);

        return i;
    }
}; // namespace libdsp