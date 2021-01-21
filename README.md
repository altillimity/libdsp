# libdsp
A library providing some common DSP functions

This was made as a standalone (no dependencies like volk required) port of GNU Radio blocks I need in some projects, but without requiring the full GNU Radio library and dependencies. Thus, this library is kept lightweight (the current .so is under 100kB), 0 dependencies apart from C++ standard ones, making it a much better choice for non-experimental projects where you want to keep things... Slim :).   

All "blocks" use a similar work function, taking an input and output buffer + the input size, returning the number of output elements. Properly feeding / reading samples for the "block" to work properly is up to the user.    
```size_t work(TYPE_IN *in, size_t length, TYPE_OUT *out);```

**All credits goes to the GNU Radio and VOLK project.**

### Features
Currently this library contains the following "blocks" or functions (C = Complex Float, F = Float, 1st is input type 2nd output) :
- AGC, CC
- DC Blocker, CC
- Costas Loop, CC
- Clock Recovery MM, CC and FF
- Moving Average, CC and FF
- BPSK Carrier PLL (NOAA HRPT PLL), CF
- PLL Carrier Tracking, CC
- Frequency Shifter, CC
- Complex to Real, CF
- Complex to Arg, CF
- Quadrature Demod, CF
- Hilbert Transform, FC
- Rational Resampler, CCF and its low-pass FIR generator function
- Root-Raised Cosine FIR generating fuction
- Low-pass FIR generating fuction
- MMSE FIR Interpolator (required by the clock recovery), CC and FF
- Noise Source, CC and FF
- Signal Source, CC
- Random number generator (used by the Noise Source)
- FFT Window generators
- Various utils functions from VOLK and GNU Radio
- A simple generic FIFO implementation (pipe.h), utilizing OS functions

### Building
This project uses CMake, so all you need to do is those commands :

```
mkdir build && cd build
cmake ..
sudo make install
```
