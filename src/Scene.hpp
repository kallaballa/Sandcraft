#ifndef SRC_SCENE_HPP_
#define SRC_SCENE_HPP_

#include <SDL/SDL.h>
#include "Config.hpp"
#include "SDLHelper.hpp"
#include "Particles.hpp"
#include "Palette.hpp"

namespace sandcraft {

class Scene {
	// The particle system play area
	SDL_Rect scene_;
	SDLHelper* SDL_;
	Particles* PARTICLES_;
	Palette* COLORS_;
public:
	Scene(SDLHelper* sdl, Particles* particles, Palette* colors) : SDL_(sdl), PARTICLES_(particles), COLORS_(colors) {
		Config& cfg = Config::getInstance();
		scene_.x = 0;
		scene_.y = 0;
		scene_.w = cfg.width_;
		scene_.h = cfg.height_ - cfg.dboard_height_;
	}
	virtual ~Scene() {}

	void draw();
};

} /* namespace sandcraft */

#endif /* SRC_SCENE_HPP_ */
