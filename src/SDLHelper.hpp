#ifndef SDLHELPER_HPP_
#define SDLHELPER_HPP_

#include <SDL/SDL.h>
#ifndef _AMIGA
#include <SDL/SDL_image.h>
#endif
#include <string>

#include "Config.hpp"
#include "GameState.hpp"

namespace sandcraft {

class SDLHelper {
private:
	Config& cfg_ = Config::getInstance();
	GameState& gs_ = GameState::getInstance();
public:
	SDL_Surface* screen_;
	SDLHelper();
	void set_pixel(Uint16 x, Uint16 y, Uint32 pixel);
	Uint32 get_pixel(SDL_Surface *surface, int x, int y);

#ifndef _AMIGA
	SDL_Surface* loadPng(std::string path);
#endif
	Uint32 hsvToRgb(float H, float S,float V);
	void drawCursor(int x, int y);
	void drawPenSize();
};
} /* namespace sandcraft */

#endif /* SDLHELPER_HPP_ */
