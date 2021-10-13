#ifndef SRC_BUTTONS_HPP_
#define SRC_BUTTONS_HPP_

#include <SDL/SDL.h>
#include "Particles.hpp"
#include "Palette.hpp"

namespace sandcraft {

// Button rectangle struct
typedef struct {
	std::string name;
	ParticleType particleType;
	Uint32 color;
} ButtonInfo;

class Buttons {
private:
	ButtonInfo info_[19];
public:

	Buttons(Palette* colors) {
		info_[0] = {"Water", WATER, (*colors)[WATER]};
		info_[1] = {"Sand", SAND, (*colors)[SAND]};
		info_[2] = {"Salt", SALT, (*colors)[SALT]};
		info_[3] = {"Oil", OIL, (*colors)[OIL]};
		info_[4] = {"Fire", FIRE, (*colors)[FIRE]};
		info_[5] = {"Acid", ACID, (*colors)[ACID]};
		info_[6] = {"Dirt", DIRT, (*colors)[DIRT]};
		info_[7] = {"Water spout", WATERSPOUT, (*colors)[WATERSPOUT]};
		info_[8] = {"Sand spout", SANDSPOUT, (*colors)[SANDSPOUT]};
		info_[9] = {"Salt spout", SALTSPOUT, (*colors)[SALTSPOUT]};
		info_[10] = {"Oil spout", OILSPOUT, (*colors)[OILSPOUT]};
		info_[11] = {"Wall", WALL, (*colors)[WALL]};
		info_[12] = {"Torch", TORCH, (*colors)[TORCH]};
		info_[13] = {"Stove", STOVE, (*colors)[STOVE]};
		info_[14] = {"Plant", PLANT, (*colors)[PLANT]};
		info_[15] = {"Ice", ICE, (*colors)[ICE]};
		info_[16] = {"Iron wall", IRONWALL, (*colors)[IRONWALL]};
		info_[17] = {"Void", NIL, (*colors)[NIL]};
		info_[18] = {"Erase", NOTHING, (*colors)[NOTHING]};
	}

	size_t size() const {
		return 19;
	}

	virtual ~Buttons() {
	}

	ButtonInfo& operator[](const size_t& i) {
		return info_[i];
	}

};

} /* namespace sandcraft */

#endif /* SRC_BUTTONS_HPP_ */
