#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include <SDL/SDL.h>

#include "Particles.hpp"

namespace sandcraft {

class Palette {
	Uint32 colors[PARTICLETYPE_ENUM_LENGTH];
public:
	virtual ~Palette() {};

	// Initializing colors
	Palette(SDL_PixelFormat* format) {
		//INERT
		colors[SAND] = SDL_MapRGB(format, 238, 204, 128);
		colors[WALL] = SDL_MapRGB(format, 100, 100, 100);
		colors[NIL] = SDL_MapRGB(format, 60, 60, 60);
		colors[IRONWALL] = SDL_MapRGB(format, 110, 110, 110);
		colors[TORCH] = SDL_MapRGB(format, 139, 69, 19);
		colors[STOVE] = SDL_MapRGB(format, 74, 74, 74);
		colors[ICE] = SDL_MapRGB(format, 175, 238, 238);
		colors[PLANT] = SDL_MapRGB(format, 0, 150, 0);
		colors[EMBER] = SDL_MapRGB(format, 127, 25, 25);
		colors[RUST] = SDL_MapRGB(format, 110, 40, 10);

		//ELEMENTAL
		colors[WATER] = SDL_MapRGB(format, 32, 32, 255);
		colors[DIRT] = SDL_MapRGB(format, 205, 175, 149);
		colors[SALT] = SDL_MapRGB(format, 255, 255, 255);
		colors[OIL] = SDL_MapRGB(format, 128, 64, 64);

		//COMBINED
		colors[MUD] = SDL_MapRGB(format, 139, 69, 19);
		colors[SALTWATER] = SDL_MapRGB(format, 65, 105, 225);
		colors[STEAM] = SDL_MapRGB(format, 95, 158, 160);

		//EXTRA
		colors[ACID] = SDL_MapRGB(format, 173, 255, 47);
		colors[FIRE] = SDL_MapRGB(format, 255, 50, 50);
		colors[ELEC] = SDL_MapRGB(format, 255, 255, 0);

		//SPOUTS
		colors[WATERSPOUT] = SDL_MapRGB(format, 0, 0, 128);
		colors[SANDSPOUT] = SDL_MapRGB(format, 240, 230, 140);
		colors[SALTSPOUT] = SDL_MapRGB(format, 238, 233, 233);
		colors[OILSPOUT] = SDL_MapRGB(format, 108, 44, 44);

	//	Uint32 step = 360.0 / PARTICLETYPE_ENUM_LENGTH;
	//	for(size_t i = 0; i < PARTICLETYPE_ENUM_LENGTH; ++i) {
	//		colors[i] = HSVtoRGB(step * i, 50, 50);
	//	}
	}

	Uint32& operator[](const ParticleType& t) {
		return colors[t];
	}
};

} /* namespace sandcraft */

#endif /* PALETTE_HPP_ */
