#include "noise_source.h"

namespace libdsp
{
    NoiseSource::NoiseSource(noise_type_t type, float ampl, long seed)
        : d_type(type),
          d_ampl(ampl),
          d_rng(seed)
    {
    }

    NoiseSource::~NoiseSource()
    {
    }

    void NoiseSource::set_type(noise_type_t type)
    {
        d_type = type;
    }

    void NoiseSource::set_amplitude(float ampl)
    {
        d_ampl = ampl;
    }

    size_t NoiseSource::work(float *out, size_t len)
    {
        switch (d_type)
        {
        case NS_UNIFORM:
            for (int i = 0; i < len; i++)
            {
                out[i] = (float)(d_ampl * ((d_rng.ran1() * 2.0) - 1.0));
            }
            break;

        case NS_GAUSSIAN:
            for (int i = 0; i < len; i++)
            {
                out[i] = (float)(d_ampl * d_rng.gasdev());
            }
            break;

        case NS_LAPLACIAN:
            for (int i = 0; i < len; i++)
            {
                out[i] = (float)(d_ampl * d_rng.laplacian());
            }
            break;

        case NS_IMPULSE: // FIXME changeable impulse settings
            for (int i = 0; i < len; i++)
            {
                out[i] = (float)(d_ampl * d_rng.impulse(9));
            }
            break;
        default:
            throw std::runtime_error("invalid type");
        }

        return len;
    }

    size_t NoiseSource::work(std::complex<float> *out, size_t len)
    {
        switch (d_type)
        {

        case NS_UNIFORM:
            for (int i = 0; i < len; i++)
            {
                out[i] = std::complex<float>(d_ampl * ((d_rng.ran1() * 2.0) - 1.0),
                                             d_ampl * ((d_rng.ran1() * 2.0) - 1.0));
            }
            break;

        case NS_GAUSSIAN:
            for (int i = 0; i < len; i++)
            {
                out[i] = d_ampl * d_rng.rayleigh_complex();
            }
            break;

        default:
            throw std::runtime_error("invalid type");
        }

        return len;
    }
} // namespace libdsp