#include "window.hpp"

std::vector<double> Window::get(std::size_t size, std::size_t type) {
    switch(type) {
        case HAMMING:
            return hamming(size);
        case BLACKMAN_HARRIS:
            return blackmanHarris(size);
        case HANN:
            return hann(size);
        case NONE:
        default:
            return none(size);
    }
}

std::vector<double> Window::blackmanHarris(std::size_t size)
{
    std::vector<double> ret;

    for (std::size_t n = 0; n < size; n++) {
        ret.push_back(
                    0.35875 - 0.48829 * cos(2. * M_PI * n / (size - 1.)) +
                    0.14128 * cos(4. * M_PI * n / (size - 1.)) -
                    0.01168 * cos(6. * M_PI * n / (size - 1.))
        );
    }

    return ret;
}

std::vector<double> Window::hamming(std::size_t size)
{
    std::vector<double> ret;

    for (std::size_t n = 0; n < size; n++) {
        ret.push_back(
                    0.54 - 0.46 * cos( M_PI * 2.0 * n / (size - 1.0) )
        );
    }

    return ret;
}

std::vector<double> Window::hann(std::size_t size)
{
    std::vector<double> ret;

    for (std::size_t n = 0; n < size; n++) {
        ret.push_back(
                    0.5 * (1.0 - cos( M_PI * 2.0 * n / (size - 1.0) ))
        );
    }

    return ret;
}

std::vector<double> Window::none(std::size_t size) {
    std::vector<double> ret(size, 1.0);
    return ret;
}