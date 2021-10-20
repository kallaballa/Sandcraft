#include "Slots.hpp"

#include <SDL/SDL.h>
#include <string>
#include "Config.hpp"
#include "GameState.hpp"


namespace sandcraft {
namespace event {

using std::string;
AG_Driver *Slots::DRV = nullptr;
AG_Window* Slots::DASHWND = nullptr;
Particles* Slots::PARTICLES = nullptr;
Buttons* Slots::BUTTONS = nullptr;

void Slots::process_events() {
	GameState& gs = GameState::getInstance();
	Config& cfg = Config::getInstance();
	AG_DriverEvent dev;
	while (AG_GetNextEvent(DRV, &dev)) {
		//Key strokes
		if (dev.type == AG_DRIVER_KEY_DOWN) {
			switch ((SDLKey)dev.data.key.ks) {
				case SDLK_ESCAPE: //Exit
					gs.done_ = 1;
					break;
				case SDLK_DELETE:
					PARTICLES->clear();
					break;
				case SDLK_LEFT:
					previous_particle();
					break;
				case SDLK_RIGHT:
					next_particle();
					break;
				case SDLK_DOWN:
					downsize_pen();
					break;
				case SDLK_UP:
					upsize_pen();
					break;
				case SDLK_RETURN:
					toggle_emit();
					break;
				case SDLK_BACKSPACE:
					set_eraser();
					break;
				case SDLK_PLUS:
					increase_density();
					break;
				case SDLK_MINUS:
					decrease_density();
					break;
				case SDLK_TAB:
					toggle_tools();
					break;
				case SDLK_LSHIFT:
				case SDLK_RSHIFT:
					gs.shift_down_ = true;
					break;
				case SDLK_LCTRL:
				case SDLK_RCTRL:
					gs.ctrl_down_ = true;
					break;
				case SDLK_LALT:
				case SDLK_RALT:
					gs.alt_down_ = true;
					break;
				default:
					break;
			}
		} else if (dev.type == AG_DRIVER_KEY_UP) {
			switch ((SDLKey)dev.data.key.ks) {
				case SDLK_LSHIFT:
				case SDLK_RSHIFT:
					gs.shift_down_ = false;
					break;
				case SDLK_LCTRL:
				case SDLK_RCTRL:
					gs.ctrl_down_ = false;
					break;
				case SDLK_LALT:
				case SDLK_RALT:
					gs.alt_down_ = false;
					break;
				default:
					break;
			}
		}
	}

	if (dev.type == AG_DRIVER_MOUSE_BUTTON_DOWN) {
		auto mbe = dev.data.button;
		if (mbe.which == AG_MOUSE_WHEELDOWN) {
			if (gs.shift_down_) {
				downsize_pen();
			} else if (gs.ctrl_down_) {
				decrease_density();
			} else if (gs.alt_down_) {
				toggle_emit();
			} else {
				next_particle();
			}
		} else if (mbe.which == AG_MOUSE_WHEELUP) {
			if (gs.shift_down_) {
				upsize_pen();
			} else if (gs.ctrl_down_) {
				increase_density();
			} else if (gs.alt_down_) {
				toggle_emit();
			} else {
				previous_particle();
			}
		} else {
			gs.oldx_ = mbe.x;
			gs.oldy_ = mbe.y;
			gs.mbx_ = mbe.x;
			gs.mby_ = mbe.y;
			gs.mouse_down_ = true;
		}
	}
	if (dev.type == AG_DRIVER_MOUSE_MOTION) {
		if (gs.mouse_down_) {
			auto mme = dev.data.motion;
//			std::cout << "motion:" << gs.oldx_ << ':' << gs.oldy_ << ':' << mme.x <<  ':' << mme.y << std::endl;
			if(gs.isHost_)
				PARTICLES->drawLine(gs.oldx_, gs.oldy_, mme.x, mme.y);
			else
				PARTICLES->triggerLineEvent(gs.oldx_, gs.oldy_, mme.x, mme.y);
			gs.oldx_ = mme.x;
			gs.oldy_ = mme.y;
		}
	} else if (dev.type == AG_DRIVER_MOUSE_BUTTON_UP) {
		gs.mbx_ = 0;
		gs.mby_ = 0;
		gs.mouse_down_ = false;
	}

	AG_ProcessEvent(DRV, &dev);
	AG_WindowProcessQueued();
}

void Slots::activate_particle(size_t i) {
	auto target = AG_ObjectFindChild(DASHWND,
			(string("button") + std::to_string(i)).c_str());
	for (size_t i = 0; i < 19; ++i) {
		auto other = AG_ObjectFindChild(DASHWND,
				(string("button") + std::to_string(i)).c_str());
		AG_SetStyle(other, "color", "#999999");
	}
	AG_SetStyle(target, "color", "#bbbbbb");
	PARTICLES->currentParticleType_ = (*BUTTONS)[i].particleType;
}

void Slots::button_handler(AG_Event* ev) {
	activate_particle(ev->argv[1].data.i);
}

void Slots::previous_particle() {
	for (int i = BUTTONS->size(); i--;) {
		if (PARTICLES->currentParticleType_ == (*BUTTONS)[i].particleType) {
			if (i > 0) {
				activate_particle(i - 1);
				PARTICLES->currentParticleType_ =
						(*BUTTONS)[i - 1].particleType;
			} else {
				activate_particle(BUTTONS->size() - 1);
				PARTICLES->currentParticleType_ =
						(*BUTTONS)[BUTTONS->size() - 1].particleType;
			}

			break;
		}
	}
}

void Slots::next_particle() {
	for (int i = BUTTONS->size(); i--;) {
		if (PARTICLES->currentParticleType_ == (*BUTTONS)[i].particleType) {
			if (i < BUTTONS->size() - 1) {
				activate_particle(i + 1);
				PARTICLES->currentParticleType_ =
						(*BUTTONS)[i + 1].particleType;
			} else {
				activate_particle(0);
				PARTICLES->currentParticleType_ = (*BUTTONS)[0].particleType;
			}

			break;
		}
	}
}

void Slots::upsize_pen() {
	GameState& gs = GameState::getInstance();
	gs.penSize_ *= 2;
	if (gs.penSize_ > 32)
		gs.penSize_ = 32;
}

void Slots::downsize_pen() {
	GameState& gs = GameState::getInstance();
	gs.penSize_ /= 2;
	if (gs.penSize_ < 1)
		gs.penSize_ = 1;

}

void Slots::toggle_emit() {
	GameState& gs = GameState::getInstance();
	gs.emitOil_ ^= true;
	gs.emitSalt_ ^= true;
	gs.emitWater_ ^= true;
	gs.emitSand_ ^= true;
}

void Slots::increase_density() {
	GameState& gs = GameState::getInstance();
	gs.oilDens_ += 0.05f;
	if (gs.oilDens_ > 1.0f)
		gs.oilDens_ = 1.0f;
	gs.saltDens_ += 0.05f;
	if (gs.saltDens_ > 1.0f)
		gs.saltDens_ = 1.0f;
	gs.waterDens_ += 0.05f;
	if (gs.waterDens_ > 1.0f)
		gs.waterDens_ = 1.0f;
	gs.sandDens_ += 0.05f;
	if (gs.sandDens_ > 1.0f)
		gs.sandDens_ = 1.0f;
}

void Slots::decrease_density() {
	GameState& gs = GameState::getInstance();
	gs.oilDens_ -= 0.05f;
	if (gs.oilDens_ < 0.05f)
		gs.oilDens_ = 0.05f;
	gs.saltDens_ -= 0.05f;
	if (gs.saltDens_ < 0.05f)
		gs.saltDens_ = 0.05f;
	gs.waterDens_ -= 0.05f;
	if (gs.waterDens_ < 0.05f)
		gs.waterDens_ = 0.05f;
	gs.sandDens_ -= 0.05f;
	if (gs.sandDens_ < 0.05f)
		gs.sandDens_ = 0.05f;
}

void Slots::quit() {
	GameState::getInstance().done_ = true;
}

void Slots::clear() {
	PARTICLES->clear();
}

void Slots::set_eraser() {
	activate_particle(18);
}

void Slots::toggle_tools() {
	if (DASHWND->visible)
		AG_WindowHide(DASHWND);
	else
		AG_WindowShow(DASHWND);
}
}

} /* namespace sandcraft */
