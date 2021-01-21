#include "hilbert_transform.h"
#include "utils.h"
#include "fir_gen.h"

#define M_TWOPI (2 * M_PI)

namespace libdsp
{
    HilbertTransform::HilbertTransform(unsigned int ntaps, fft::window::win_type window, double beta) : d_ntaps(ntaps | 0x1), // ensure ntaps is odd
                                                                                                        d_hilb(1, firgen::hilbert(d_ntaps, window, beta))
    {
    }

    HilbertTransform::~HilbertTransform()
    {
    }

    size_t HilbertTransform::work(float *in, size_t length, std::complex<float> *out)
    {
        tmp_.insert(tmp_.end(), in, &in[length]);

        int ii = 0;

        for (int i = 0; i < tmp_.size(); i++)
        {
            out[ii++] = std::complex<float>(tmp_[i + d_ntaps / 2], d_hilb.filter(&tmp_[i]));
        }

        tmp_.erase(tmp_.begin(), tmp_.end() - d_ntaps);

        return ii;
    }
} // namespace libdsp