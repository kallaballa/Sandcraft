#ifndef SRC_DASHBOARD_HPP_
#define SRC_DASHBOARD_HPP_

#include <SDL/SDL.h>
#include "SDLHelper.hpp"
#include "Config.hpp"

namespace sandcraft {

class Dashboard {
	SDLHelper* sdl_;
public:
	Dashboard(SDLHelper* sdl) : sdl_(sdl) {
	}
	virtual ~Dashboard() {}

	void draw() {
		Config& cfg = Config::getInstance();
		//set up dashboard
		SDL_Rect dashboard;
		dashboard.x = 0;
		dashboard.y = cfg.height_ - cfg.dboard_height_;
		dashboard.w = cfg.width_;
		dashboard.h = cfg.dboard_height_;
		SDL_FillRect(sdl_->screen_, &dashboard,
		SDL_MapRGB(sdl_->screen_->format, 155, 155, 155));
//		SDL_UpdateRect(sdl_->screen_, dashboard.x, dashboard.y, dashboard.w,
//				dashboard.h);
	}
};

} /* namespace sandcraft */

#endif /* SRC_DASHBOARD_HPP_ */
