#include "Scene.hpp"
#include "GameState.hpp"
namespace sandcraft {

//Drawing our virtual SDL->screen to the real SDL->screen
void Scene::draw() {
	Config& cfg = Config::getInstance();
	GameState& gs = GameState::getInstance();
	gs.particleCount_ = 0;


	//Locking the SDL->screen

	//Clearing the SDL->screen with black
	//memset(SDL_->screen_->pixels, 0, cfg.width_ * cfg.height_ * SDL_->screen_->format->BytesPerPixel);

	//Iterating through each pixel height first
	for (int y = cfg.height_ - cfg.dboard_height_; y--;) {
		//Width
		for (int x = cfg.width_; x--;) {
			int index = x + (cfg.width_ * y);
			ParticleType same = (*PARTICLES_)[index];
			if (same != NOTHING) {
				if (Particles::isInert(same))
					SDL_->set_pixel(x, y, (*COLORS_)[same]);
				else {
					gs.particleCount_++;
					if (same % 2 == 1) {
						//Moved
						SDL_->set_pixel(x, y, (*COLORS_)[ParticleType(same - 1)]);
						(*PARTICLES_)[index] = (ParticleType) (same - 1); //Set it to not moved
					} else
						//Not moved
						SDL_->set_pixel(x, y, (*COLORS_)[same]);
				}
			} else {
				SDL_->set_pixel(x, y, 0);
			}
		}
	}
}

} /* namespace sandcraft */
