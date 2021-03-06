
#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <X11/Xlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_stdinc.h>
#include <agar/core.h>
#include <agar/gui.h>
#include <zlib.h>

#include <thread>
#include <functional>
#include <cassert>
#include "CmdLine.hpp"
#include "SDLHelper.hpp"
#include "Palette.hpp"
#include "GameState.hpp"
#include "Buttons.hpp"
#include "Dashboard.hpp"
#include "Selection.hpp"
#include "Scene.hpp"
#include "Error.hpp"
#include "Slots.hpp"
#include "Nexus.hpp"
#include "WebRTC.hpp"
#include "Logger.hpp"


#ifdef __EMSCRIPTEN__
#include "SDL_emscripten.hpp"
#endif
using namespace sandcraft;

namespace sandcraft {

Palette* COLORS = nullptr;
Particles* PARTICLES = nullptr;
SDLHelper* SDL = nullptr;
Scene* SCENE = nullptr;
AG_Window* HELPWND = nullptr;
AG_Window* DASHWND = nullptr;

Buttons* BUTTONS = nullptr;
std::thread* EVTHREAD = nullptr;
AG_Driver* DRV = nullptr;
Nexus* NEXUS = nullptr;
std::mutex INIT_NEXUS_MTX;

void initNexus() {
	std::unique_lock<std::mutex> lock(INIT_NEXUS_MTX);
	log_info("Init Nexus");
	Config& cfg = Config::getInstance();
	if(NEXUS != nullptr) {
		delete NEXUS;
	}

	NEXUS = new Nexus("phokis.at", cfg.port_);
	NEXUS->initRTC(
			[&](std::vector<byte> data) {
		if(NEXUS != nullptr && NEXUS->isOpen()) {
					if(!GameState::getInstance().isHost_) {
//						NEXUS->receiveParticleRow(data, PARTICLES);
						NEXUS->receiveParticles(data, PARTICLES);
					} else {
						NEXUS->receiveDrawLine(data, PARTICLES);
					}
				}
			});
}

void init() {
	log_info("Initializing");
	try {
		Config& cfg = Config::getInstance();
		cfg.btn_upper_row_y_ = cfg.height_ - cfg.btn_size_ - 4;
		cfg.btn_middle_row_y_ = cfg.height_ - cfg.btn_size_ - 4;
		cfg.btn_lower_row_y_ = cfg.height_ - cfg.btn_size_ - 4;
		cfg.dboard_height_ = cfg.btn_size_ + 8;

		initNexus();
		PARTICLES =
				new Particles(
						[&](int newx, int newy, int oldx, int oldy, ParticleType type) {
							if(NEXUS != nullptr && !GameState::getInstance().isHost_ && NEXUS->isOpen()) {
								NEXUS->sendDrawLine(newx, newy, oldx, oldy, type, GameState::getInstance().penSize_);
							}
						});
		SDL = new SDLHelper();
		COLORS = new Palette(SDL->screen_->format);
		SCENE = new Scene(SDL, PARTICLES, COLORS);
		BUTTONS = new Buttons(COLORS);

		if (HELPWND == nullptr) {
			AG_InitVideoSDL(SDL->screen_,
			AG_VIDEO_DOUBLEBUF);

			DASHWND = AG_WindowNew(
					AG_WINDOW_MAIN | AG_WINDOW_NOTITLE | AG_WINDOW_NOMOVE
							| AG_WINDOW_NOMAXIMIZE);
			AG_WidgetSetSize(DASHWND, cfg.width_ / 10, cfg.height_);
			AG_WindowSetCaption(DASHWND, "%s", "");
			AG_WindowSetPosition(DASHWND, AG_WINDOW_TL, 1);

			for (size_t i = 0; i < BUTTONS->size(); ++i) {
				auto btn = AG_ButtonNewFn(DASHWND, AG_BUTTON_HFILL,
						(*BUTTONS)[i].name.c_str(),
						event::Slots::button_handler, "%d", (i));
				string c = utils::int_to_hex_color(SDL->screen_->format,
						(*BUTTONS)[i].color);
				AG_SetStyle(btn, "padding", "2");
				AG_SetStyle(btn, "font-size", "60%");
				AG_SetStyle(btn, "font-weight", "bold");
				AG_SetStyle(btn, "text-color", c.c_str());
				AG_SetStyle(btn, "color", "#999999");
			}
			AG_WindowShow(DASHWND);

			HELPWND = AG_WindowNew(
					AG_WINDOW_MAIN | AG_WINDOW_NOTITLE | AG_WINDOW_MAXIMIZED
							| AG_WINDOW_NOHRESIZE | AG_WINDOW_NOVRESIZE
							| AG_WINDOW_MODAL);
			AG_SetStyle(HELPWND, "font-size", "60%");
			auto pane = AG_PaneNewHoriz(HELPWND, AG_PANE_VFILL | AG_PANE_HFILL);
//			auto tb1 =
					AG_LabelNew(pane->div[0], AG_LABEL_EXPAND,
							"Sandcraft\n"
									"---------\n"
									"The aim of this program is to simulate different\n"
									"particles (such as sand, water, oil or fire)\n"
									"interacting with each other.\n"
									"\n"
									"Freedom is given to the player to experiment with\n"
									"the different materials in a sandbox environment.\n"
									"\n"
									"Usage\n"
									"---------\n"
									"Select a brush type from the panel on the left part of\n"
									"the screen and draw while pressing the left mouse button.\n");
//			auto tb2 =
					AG_LabelNew(pane->div[1], AG_LABEL_EXPAND, "Keymap\n"
					"---------\n"
					"ESC: Exit game\n"
					"DELETE: Clear screen\n"
					"MOUSE: Move cursor\n"
					"LEFT/RIGHT: change brush type\n"
					"UP/DOWN: increase/decrease pen size\n"
					"LEFT MOUSE BUTTON: paint w/ selected brush type\n"
					"BACKSPACE: set the brush type to eraser\n"
					"RETURN: turn on/off emitters\n"
					"PLUS/MINUS: decrease/increase emitters density\n"
					"TAB: hide/show the toolbar.");
			AG_ButtonNewFn(HELPWND, AG_BUTTON_HFILL, "Close", AGWINHIDE(HELPWND));
			AG_WindowSetPosition(HELPWND, AG_WINDOW_TC, 1);
			AG_WindowShow(HELPWND);
		} else {
			AG_SetVideoSurfaceSDL(SDL->screen_);
//			AG_ObjectDestroy(WINDOW);
		}
		DRV = (AG_Driver *) agDriverSw;
		event::Slots::init(DRV, DASHWND, PARTICLES, BUTTONS);
		EVTHREAD = new std::thread([&]() {
			while(true) {
				std::unique_lock<std::mutex> lock(INIT_NEXUS_MTX);
				event::Slots::process_events();
				std::this_thread::yield();
			}
		});
	} catch (std::exception& ex) {
		log_error("Exception", ex.what());
	}
	GameState::getInstance().done_ = 0;
	std::cout << "loaded" << std::endl;
}

#ifdef __EMSCRIPTEN__
EM_JS(int, get_canvas_width, (), {if(document) {return document.getElementById("content").clientWidth;} else {return 640;}});
EM_JS(int, get_canvas_height, (), {if(document) {return document.getElementById("content").clientHeight;} else {return 360;}});
#else
int get_canvas_width() {
	return SDL->screen_->w;
}
;
int get_canvas_height() {
	return SDL->screen_->h;
}
;
#endif

void destroy() {
	GameState::getInstance().done_ = 1;
#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif
	if (SDL != nullptr)
		delete SDL;
	if (COLORS != nullptr)
		delete COLORS;
	if (PARTICLES != nullptr)
		delete PARTICLES;
	if (SCENE != nullptr)
		delete SCENE;
}

std::function<void()> STEP_FUNC;

void step() {
	try {
		STEP_FUNC();
	} catch (std::exception& ex) {
		log_error("Exception", ex.what());
	}
}

}

void single_player_step(long& tick, Uint32& t1, Uint32& t2) {
	try {
		tick++;
		t2 = AG_GetTicks();
		if (t2 - t1 >= 1000 / 30) {
			if (NEXUS != nullptr && NEXUS->isClosed()) {
				(*COLORS)[NOTHING] = 0xFF0000FF;
				initNexus();
			} else if (NEXUS != nullptr && NEXUS->isOpen()) {
				(*COLORS)[NOTHING] = 0x00000000;
			} else {
				(*COLORS)[NOTHING] = 0xFF111111;
			}

			if (NEXUS != nullptr && GameState::getInstance().isHost_ && NEXUS->isOpen()) {
				if(NEXUS->rtc_->dc_->bufferedAmount() == 0) {
					NEXUS->sendParticles(*PARTICLES);

//				for(size_t y = 0; y < cfg.height_; ++y) {
//					NEXUS->sendParticleRow(y,*PARTICLES);
//				}
				}
			}

			if (SDL_MUSTLOCK(SDL->screen_)) {
				if (SDL_LockSurface(SDL->screen_) < 0) {
					return;
				}
			}

			SCENE->draw();

			if (DASHWND != nullptr && AG_WindowIsVisible(DASHWND)) {
				AG_WindowDraw(DASHWND);
			}
			if (HELPWND != nullptr && AG_WindowIsVisible(HELPWND)) {
				AG_WindowDraw(HELPWND);
			}

			//SDL->drawCursor(gs.oldx_, gs.oldy_);
			if (SDL_MUSTLOCK(SDL->screen_)) {
				SDL_UnlockSurface(SDL->screen_);
			}
			SDL_Flip(SDL->screen_);
			t1 = AG_GetTicks();
		}
		AG_ProcessTimeouts(t2);
		PARTICLES->logic();
	} catch (std::exception& ex) {
		log_error("Exception", ex.what());
	} catch (...) {
		log_error("Unknown exception");
	}
	std::this_thread::yield();
}

int main(int argc, char **argv) {
	using namespace sandcraft;
#ifndef __EMSCRIPTEN__
	XInitThreads();
#endif
	Logger::init(L_GLOBAL);
	ErrorHandler::init([](const string& msg){
		log_error("Error", msg);
	});

	if (AG_InitCore(NULL, AG_SOFT_TIMERS) == -1)
		return 2;

	CCmdLine cmdLine;
	Config& cfg = Config::getInstance();
	GameState& gs = GameState::getInstance();

	// parse the command line.
	if (cmdLine.SplitLine(argc, argv) < 1) {
		// no switches were given on the command line
		//Set default size
		cfg.width_ = 640;
		cfg.height_ = 360;
	} else {
		// StringType is defined in CmdLine.h.
		// it is CString when using MFC, else STL's 'string'
		StringType height, width;

		// get the required arguments
		try {
			// if any of these GetArgument calls fail,
			// we'll end up in the catch() block
			width = cmdLine.GetArgument("-width", 0);
			height = cmdLine.GetArgument("-height", 0);
			cfg.width_ = atoi(width.c_str());
			cfg.height_ = atoi(height.c_str());
		} catch (...) {
			// one of the required arguments was missing, abort
			exit(-1);
		}
	}
	init();
	// Set initial seed
	utils::srand();

	gs.oldx_ = cfg.width_ / 2, gs.oldy_ = cfg.height_ / 2;

	long tick = 0;
	Uint32 t1, t2;
	t1 = AG_GetTicks();

	STEP_FUNC = [&]() {
		single_player_step(tick, t1, t2);
	};

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(step, 0, 1);
#else
	while (!gs.done_)
		step();
#endif
	//Loop ended - quit SDL
	SDL_Quit();
	if (SDL_NumJoysticks() > 0)
		SDL_JoystickClose(0);

	return 0;
}

extern "C" {

int load_image(char* file_path, bool copyPalette) {
	using namespace sandcraft;
	Config& cfg = Config::getInstance();
	SDL_Surface* img = SDL->loadPng(file_path);
	if(img->w == 0 && img->h == 0) {
		log_warn("Empty image loaded");
		return 1;
	}

	off_t w = img->w;
	off_t h = img->h;
	off_t offx = (cfg.width_ - img->w) / 2;
	off_t offy = (cfg.height_ - img->h) / 2;

	if(img->w > cfg.width_ || img->h > cfg.height_) {
		w = cfg.width_;
		h = cfg.height_;
		offx = 0;
		offy = 0;
	}
	for (size_t x = 0; x < w; ++x) {
		for (size_t y = 0; y < h; ++y) {
			Uint32 p = SDL->get_pixel(img, x, y);
			(*PARTICLES)[offx + x + ((offy + y) * cfg.width_)] = ParticleType(
					((p % PARTICLETYPE_ENUM_LENGTH))
							% PARTICLETYPE_ENUM_LENGTH);
		}
	}
	if (copyPalette) {
		for (size_t x = 0; x < w; ++x) {
			for (size_t y = 0; y < h; ++y) {
				Uint32 p = SDL->get_pixel(img, x, y);
				int index = p % PARTICLETYPE_ENUM_LENGTH;
				Uint8 r, g, b;
				SDL_GetRGB(p, img->format, &r, &g, &b);
				(*COLORS)[(ParticleType) index] = SDL_MapRGB(
						SDL->screen_->format, r, g, b);
			}
		}
	}
	return 0;
}
}
