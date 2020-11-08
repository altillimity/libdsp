#include "fir_filter_imp.h"
#include <algorithm>
#include "utils.h"

namespace libdsp
{
    fir_filter_cc::fir_filter_cc(int decimation, const std::vector<float> &taps) : d_output(1)
    {
        d_align = 1; //volk_get_alignment();
        d_naligned = std::max((size_t)1, d_align / sizeof(std::complex<float>));
        set_taps(taps);
    }

    fir_filter_cc::~fir_filter_cc()
    {
    }

    void fir_filter_cc::set_taps(const std::vector<float> &taps)
    {
        d_ntaps = (int)taps.size();
        d_taps = taps;
        std::reverse(d_taps.begin(), d_taps.end());

        d_aligned_taps.clear();
        d_aligned_taps = std::vector<std::vector<float>>(
            d_naligned, std::vector<float>((d_ntaps + d_naligned - 1), 0));
        for (int i = 0; i < d_naligned; i++)
        {
            for (unsigned int j = 0; j < d_ntaps; j++)
                d_aligned_taps[i][i + j] = d_taps[j];
        }
    }

    void fir_filter_cc::update_tap(float t, unsigned int index)
    {
        d_taps[index] = t;
        for (int i = 0; i < d_naligned; i++)
        {
            d_aligned_taps[i][i + index] = t;
        }
    }

    std::vector<float> fir_filter_cc::taps() const
    {
        std::vector<float> t = d_taps;
        std::reverse(t.begin(), t.end());
        return t;
    }

    unsigned int fir_filter_cc::ntaps() const
    {
        return d_ntaps;
    }

    std::complex<float> fir_filter_cc::filter(const std::complex<float> input[]) const
    {
        const std::complex<float> *ar = (std::complex<float> *)((size_t)input & ~(d_align - 1));
        unsigned al = input - ar;

        volk_32fc_32f_dot_prod_32fc_generic(const_cast<std::complex<float> *>(d_output.data()), ar, d_aligned_taps[al].data(), (d_ntaps + al));
        return d_output[0];
    }

    void fir_filter_cc::filterN(std::complex<float> output[], const std::complex<float> input[], unsigned long n)
    {
        for (unsigned long i = 0; i < n; i++)
        {
            output[i] = filter(&input[i]);
        }
    }

    void fir_filter_cc::filterNdec(std::complex<float> output[], const std::complex<float> input[], unsigned long n, unsigned int decimate)
    {
        unsigned long j = 0;
        for (unsigned long i = 0; i < n; i++)
        {
            output[i] = filter(&input[j]);
            j += decimate;
        }
    }

    fir_filter_ff::fir_filter_ff(int decimation, const std::vector<float> &taps) : d_output(1)
    {
        d_align = 1; //volk_get_alignment();
        d_naligned = std::max((size_t)1, d_align / sizeof(float));
        set_taps(taps);
    }

    fir_filter_ff::~fir_filter_ff()
    {
    }

    void fir_filter_ff::set_taps(const std::vector<float> &taps)
    {
        d_ntaps = (int)taps.size();
        d_taps = taps;
        std::reverse(d_taps.begin(), d_taps.end());

        d_aligned_taps.clear();
        d_aligned_taps = std::vector<std::vector<float>>(
            d_naligned, std::vector<float>((d_ntaps + d_naligned - 1), 0));
        for (int i = 0; i < d_naligned; i++)
        {
            for (unsigned int j = 0; j < d_ntaps; j++)
                d_aligned_taps[i][i + j] = d_taps[j];
        }
    }

    void fir_filter_ff::update_tap(float t, unsigned int index)
    {
        d_taps[index] = t;
        for (int i = 0; i < d_naligned; i++)
        {
            d_aligned_taps[i][i + index] = t;
        }
    }

    std::vector<float> fir_filter_ff::taps() const
    {
        std::vector<float> t = d_taps;
        std::reverse(t.begin(), t.end());
        return t;
    }

    unsigned int fir_filter_ff::ntaps() const
    {
        return d_ntaps;
    }

    float fir_filter_ff::filter(const float input[]) const
    {
        const float *ar = (float *)((size_t)input & ~(d_align - 1));
        unsigned al = input - ar;

        volk_32f_x2_dot_prod_32f_generic(const_cast<float *>(d_output.data()), ar, d_aligned_taps[al].data(), d_ntaps + al);
        return d_output[0];
    }

    void fir_filter_ff::filterN(float output[], const float input[], unsigned long n)
    {
        for (unsigned long i = 0; i < n; i++)
        {
            output[i] = filter(&input[i]);
        }
    }

    void fir_filter_ff::filterNdec(float output[], const float input[], unsigned long n, unsigned int decimate)
    {
        unsigned long j = 0;
        for (unsigned long i = 0; i < n; i++)
        {
            output[i] = filter(&input[j]);
            j += decimate;
        }
    }
} // namespace libdsp