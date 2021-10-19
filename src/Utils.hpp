#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_

#include <string>
#include <cstdint>
#include <random>
#include <algorithm>
#include <SDL/SDL.h>

namespace sandcraft {

// utils.hpp
namespace utils {
	std::vector<std::string> split(const std::string& s, const char& by);
	std::string int_to_hex_color(SDL_PixelFormat* format, uint32_t i);
	void srand(unsigned int seed);
    void srand();
    unsigned int rand();
    std::string random_id(size_t length);
    char* b64_encode(const unsigned char *in, size_t len);
    size_t b64_decoded_size(const char *in);
    int b64_decode(const char *in, unsigned char *out, size_t outlen);
}

} /* namespace sandcraft */

#endif /* SRC_UTILS_HPP_ */
