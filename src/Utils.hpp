#ifndef SRC_UTILS_HPP_
#define SRC_UTILS_HPP_

#include <string>
#include <cstdint>
#include <SDL/SDL.h>

namespace sandcraft {

// utils.hpp
namespace utils {
	std::string int_to_hex_color(SDL_PixelFormat* format, uint32_t i);
	void srand(unsigned int seed);
    void srand();
    unsigned int rand();
}

} /* namespace sandcraft */

#endif /* SRC_UTILS_HPP_ */
