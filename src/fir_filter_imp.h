#pragma once

#include <complex>
#include <vector>

namespace libdsp
{
    class fir_filter_cc
    {
    public:
        fir_filter_cc(int decimation, const std::vector<float> &taps);
        ~fir_filter_cc();

        // Disallow copy.
        //
        // This prevents accidentally doing needless copies, not just of fir_filter_cc,
        // but every block that contains one.
        fir_filter_cc(const fir_filter_cc &) = delete;
        fir_filter_cc(fir_filter_cc &&) = default;
        fir_filter_cc &operator=(const fir_filter_cc &) = delete;
        fir_filter_cc &operator=(fir_filter_cc &&) = default;

        void set_taps(const std::vector<float> &taps);
        void update_tap(float t, unsigned int index);
        std::vector<float> taps() const;
        unsigned int ntaps() const;

        std::complex<float> filter(const std::complex<float> input[]) const;
        void filterN(std::complex<float> output[], const std::complex<float> input[], unsigned long n);
        void filterNdec(std::complex<float> output[],
                        const std::complex<float> input[],
                        unsigned long n,
                        unsigned int decimate);

    protected:
        std::vector<float> d_taps;
        unsigned int d_ntaps;
        std::vector<std::vector<float>> d_aligned_taps;
        std::vector<std::complex<float>> d_output;
        int d_align;
        int d_naligned;
    };

    class fir_filter_ff
    {
    public:
        fir_filter_ff(int decimation, const std::vector<float> &taps);
        ~fir_filter_ff();

        // Disallow copy.
        //
        // This prevents accidentally doing needless copies, not just of fir_filter,
        // but every block that contains one.
        fir_filter_ff(const fir_filter_ff &) = delete;
        fir_filter_ff(fir_filter_ff &&) = default;
        fir_filter_ff &operator=(const fir_filter_ff &) = delete;
        fir_filter_ff &operator=(fir_filter_ff &&) = default;

        void set_taps(const std::vector<float> &taps);
        void update_tap(float t, unsigned int index);
        std::vector<float> taps() const;
        unsigned int ntaps() const;

        float filter(const float input[]) const;
        void filterN(float output[], const float input[], unsigned long n);
        void filterNdec(float output[],
                        const float input[],
                        unsigned long n,
                        unsigned int decimate);

    protected:
        std::vector<float> d_taps;
        unsigned int d_ntaps;
        std::vector<std::vector<float>> d_aligned_taps;
        std::vector<float> d_output;
        int d_align;
        int d_naligned;
    };
} // namespace libdsp