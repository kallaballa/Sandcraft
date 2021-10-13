#include "Utils.hpp"
#include <time.h>
#include <sstream>
#include <iomanip>

namespace sandcraft {

namespace {
    static unsigned int s_rand_high = 1;
    static unsigned int s_rand_low = 1 ^ 0x49616E42;
}


std::string utils::int_to_hex_color(SDL_PixelFormat* format, uint32_t i) {
	uint8_t r, g, b;
	SDL_GetRGB(i, format, &r, &g, &b);
	std::stringstream stream;
	stream << "#" << std::setfill('0') << std::setw(2) << std::hex << (int) r
			<< std::setfill('0') << std::setw(2) << std::hex << (int) g
			<< std::setfill('0') << std::setw(2) << std::hex << (int) b;
	return stream.str();
}

void utils::srand(unsigned int seed)
{
    s_rand_high = seed;
    s_rand_low = seed ^ 0x49616E42;
}

void utils::srand()
{
    utils::srand(static_cast<unsigned int>(time(0)));
}

unsigned int utils::rand() {
    static const int shift = sizeof(int) / 2;
    s_rand_high = (s_rand_high >> shift) + (s_rand_high << shift);
    s_rand_high += s_rand_low;
    s_rand_low += s_rand_high;
    return s_rand_high;
}

} /* namespace sandcraft */
