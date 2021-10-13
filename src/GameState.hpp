#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

namespace sandcraft {

class GameState {
private:
	static GameState* instance_;
	GameState(){};
public:
	int particleCount_ = 0;
	int penSize_ = 2;

	int mbx_ = 0;
	int mby_ = 0;

	int oldx_ = 0;
	int oldy_ = 0;

	bool emitWater_ = true;
	bool emitSand_ = true;
	bool emitSalt_ = true;
	bool emitOil_ = true;

	//Initial density of emitters
	float waterDens_ = 0.3f;
	float sandDens_ = 0.3f;
	float saltDens_ = 0.3f;
	float oilDens_ = 0.3f;

	bool done_ = 0;
	bool mouse_down_ = false;
	bool ctrl_down_ = false;
	bool alt_down_ = false;
	bool shift_down_ = false;

	static GameState& getInstance() {
		if(instance_ == nullptr)
			instance_ = new GameState();

		return *instance_;
	}
};

} /* namespace sandcraft */

#endif /* GAMESTATE_HPP_ */
