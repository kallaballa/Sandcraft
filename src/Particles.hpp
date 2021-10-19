#ifndef PARTICLES_HPP_
#define PARTICLES_HPP_

#include "Config.hpp"
#include "GameState.hpp"
#include <iostream>
#include <queue>
#include <mutex>

namespace sandcraft {

/*
 Enumerating concentions
 -----------------------
 Inert: between INERT_UPPER_BOUND and INERT_LOWER_BOUND
 Floating: between FLOATING_UPPER_BOUND and FLOATING_LOWER_BOUND
 */
const int INERT_UPPER_BOUND = 13;
const int INERT_LOWER_BOUND = 0;
const int FLOATING_UPPER_BOUND = 33;
const int FLOATING_LOWER_BOUND = 30;

const int PARTICLETYPE_ENUM_LENGTH = 36;

enum ParticleType {
	// INERT
	NOTHING = 0,
	WALL = 1,
	IRONWALL = 2,
	TORCH = 3,
	//x = 4,
	STOVE = 4,
	ICE = 5,
	RUST = 6,
	EMBER = 7,
	PLANT = 8,
	NIL = 9,

	//SPOUTS
	WATERSPOUT = 10,
	SANDSPOUT = 11,
	SALTSPOUT = 12,
	OILSPOUT = 13,
	//x = 15,

	//ELEMENTAL
	WATER = 14,
	MOVEDWATER = 15,
	DIRT = 16,
	MOVEDDIRT = 17,
	SALT = 18,
	MOVEDSALT = 19,
	OIL = 20,
	MOVEDOIL = 21,
	SAND = 22,
	MOVEDSAND = 23,

	//COMBINED
	SALTWATER = 24,
	MOVEDSALTWATER = 25,
	MUD = 26,
	MOVEDMUD = 27,
	ACID = 28,
	MOVEDACID = 29,

	//FLOATING
	STEAM = 30,
	MOVEDSTEAM = 31,
	FIRE = 32,
	MOVEDFIRE = 33,

	//Electricity
	ELEC = 34,
	MOVEDELEC = 35
};

struct LineEvent {
	int newX_ = 0;
	int newY_ = 0;
	int oldX_ = 0;
	int oldY_ = 0;
};

class Particles {
private:
	//Instead of using a two dimensional array
	// we'll use a simple array to improve speed
	// vs = virtual screen


	// The current brush type
	GameState& gs_ = GameState::getInstance();
	Config& config_ = Config::getInstance();
	std::queue<LineEvent> lineQ_;
	std::mutex levmtx_;
public:
	ParticleType *vs_;
	ParticleType currentParticleType_ = WALL;
	std::function<void(int, int, int, int, ParticleType)> drawLineCallback_;
	Particles(std::function<void(int, int, int, int, ParticleType)> drawLineCallback) {
		vs_ = new ParticleType[config_.width_ * config_.height_];
		drawLineCallback_ = drawLineCallback;
	}

	void triggerLineEvent(int newx, int newy, int oldx, int oldy) {
		std::unique_lock<std::mutex>(levmtx_);
		lineQ_.push({newx , newy, oldx, oldy});
	}

	//Checks wether a given particle type is a inert element
	static inline bool isInert(ParticleType t) {
		return (t >= INERT_LOWER_BOUND && t <= INERT_UPPER_BOUND);
	}

	//Checks wether a given particle type is a floting type - like FIRE and STEAM
	static inline bool isFloating(ParticleType t) {
		return (t >= FLOATING_LOWER_BOUND && t <= FLOATING_UPPER_BOUND);
	}

	//Checks wether a given particle type is burnable - like PLANT and OIL
	static inline bool isBurnable(ParticleType t) {
		return (t == PLANT || t == OIL || t == MOVEDOIL);
	}

	//Checks wether a given particle type is burnable - like PLANT and OIL
	static inline bool burnsAsEmber(ParticleType t) {
		return (t == PLANT); //Maybe we'll add a FUSE or WOOD
	}


	ParticleType& operator[](const size_t& i) {
		return vs_[i];
	}

	void emit(int x, int width, ParticleType type, float p);
	void inertParticleLogic(int x, int y, ParticleType type);
	void moveParticle(int x, int y, ParticleType type);
	void drawParticles(int xpos, int ypos, int radius, ParticleType type);
	void drawLine(int newx, int newy, int oldx, int oldy);
	void drawLine(int newx, int newy, int oldx, int oldy, ParticleType type, int penSize);
	void doRandomLines(ParticleType type);
	void updateVirtualPixel(int x, int y);
	void updateVirtualScreen();
	void logic();
	void clear();
};

} /* namespace sandcraft */

#endif /* PARTICLES_HPP_ */
