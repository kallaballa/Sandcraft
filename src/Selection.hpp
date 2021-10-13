#ifndef SRC_SELECTION_HPP_
#define SRC_SELECTION_HPP_

#include "SDLHelper.hpp"
#include "Buttons.hpp"

namespace sandcraft {

class Selection {
	SDLHelper* sdl_;
	Particles* particles_;
	Buttons* buttons_;
public:
	Selection(SDLHelper* sdl, Particles* particles, Buttons* buttons) : sdl_(sdl), particles_(particles), buttons_(buttons){
	}

	virtual ~Selection() {}

	void draw();
};

} /* namespace sandcraft */

#endif /* SRC_SELECTION_HPP_ */
