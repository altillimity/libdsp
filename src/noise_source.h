#pragma once

#include "random.h"

namespace libdsp
{
    typedef enum
    {
        NS_UNIFORM = 200,
        NS_GAUSSIAN,
        NS_LAPLACIAN,
        NS_IMPULSE
    } noise_type_t;

    class NoiseSource
    {
    private:
        noise_type_t d_type;
        float d_ampl;
        Random d_rng;

    public:
        NoiseSource(noise_type_t type, float ampl, long seed = 0);
        ~NoiseSource();

        void set_type(noise_type_t type);
        void set_amplitude(float ampl);

        noise_type_t type() const { return d_type; }
        float amplitude() const { return d_ampl; }

        size_t work(float *out, size_t len);
        size_t work(std::complex<float> *out, size_t len);
    };
} // namespace libdsp