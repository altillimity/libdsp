#pragma once

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace libdsp
{
    /*
    Simple generic FIFO implementation using the pipe Unix / Linux and Windows implementation.
    */
    template <typename T>
    class Pipe
    {
    private:
        // File handles
        int fifo_handles[2];
        // Util values
        int read_cnt;
        int read_tries;

    public:
        // The buffer size is only used on Windows currently
        Pipe(int buffer_size = 4096)
        {
#ifdef _WIN32
            _pipe(fifo_handles, buffer_size * 10 * sizeof(std::complex<float>), 'b');
#else
            pipe(fifo_handles);
#endif
        }
        // Close everything
        ~Pipe()
        {
            if (fifo_handles[1])
                close(fifo_handles[1]);
            if (fifo_handles[0])
                close(fifo_handles[0]);
        }
        // Push x samples into the fifo
        void push(T *buffer, int size)
        {
            write(fifo_handles[1], buffer, size * sizeof(T));
        }
        // Read x samples from the fifo, trying to fill the request
        int pop(T *buffer, int size, int tries = 100)
        {
            read_cnt = 0;
            read_tries = 0;
            while (read_cnt < size && read_tries < tries)
            {
                read_cnt += read(fifo_handles[0], &buffer[read_cnt], (size - read_cnt) * sizeof(T)) / sizeof(T);
                read_tries++;
            }
            return read_cnt;
        }
        // Read x samples from the fifo, with what's in the buffer
        int pop_eager(T *buffer, int size)
        {
            return read(fifo_handles[0], buffer, size * sizeof(T)) / sizeof(T);
        }
    };
}; // namespace libdsp
