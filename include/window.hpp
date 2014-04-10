#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <math.h>

class Window
{
public:
    enum {
        NONE,
        HAMMING,
        BLACKMAN_HARRIS,
        HANN
    };
    static std::vector<double> get(std::size_t size, std::size_t type = 0);
    static std::vector<double> blackmanHarris(std::size_t size);
    static std::vector<double> hamming(std::size_t size);
    static std::vector<double> hann(std::size_t size);
    static std::vector<double> none(std::size_t size);
};

#endif // WINDOW_HPP
