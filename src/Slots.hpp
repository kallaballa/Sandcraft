#ifndef SRC_SLOTS_HPP_
#define SRC_SLOTS_HPP_

#include <agar/core.h>
#include <agar/gui.h>
#include "Particles.hpp"
#include "Buttons.hpp"
namespace sandcraft {
namespace event {

class Slots {
private:
	static AG_Driver *DRV;
	static AG_Window* DASHWND;
	static Particles* PARTICLES;
	static Buttons* BUTTONS;
public:
	static void init(AG_Driver* drv, AG_Window* dashwnd, Particles* particles,
			Buttons* buttons) {
		DASHWND = dashwnd;
		DRV = drv;
		PARTICLES = particles;
		BUTTONS = buttons;
	}

	static void process_events();
	static void activate_particle(size_t i);
	static void button_handler(AG_Event* ev);
	static void previous_particle();
	static void next_particle();
	static void upsize_pen();
	static void downsize_pen();
	static void toggle_emit();
	static void increase_density();
	static void decrease_density();
	static void quit();
	static void clear();
	static void set_eraser();
	static void toggle_tools();
};
}

} /* namespace sandcraft */

#endif /* SRC_SLOTS_HPP_ */
