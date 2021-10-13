#ifndef PARTICLES_HPP_
#define PARTICLES_HPP_

#include "Config.hpp"
#include "GameState.hpp"
#include <iostream>

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

class Particles {
private:
	//Instead of using a two dimensional array
	// we'll use a simple array to improve speed
	// vs = virtual screen
	ParticleType *vs_;

	// The current brush type
	GameState& gs_ = GameState::getInstance();
	Config& config_ = Config::getInstance();
public:
	ParticleType currentParticleType_ = WALL;

	Particles() {
		vs_ = new ParticleType[config_.width_ * config_.height_];
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

	void Emit(int x, int width, ParticleType type, float p);
	void InertParticleLogic(int x, int y, ParticleType type);
	void MoveParticle(int x, int y, ParticleType type);
	void DrawParticles(int xpos, int ypos, int radius, ParticleType type);
	void DrawLine(int newx, int newy, int oldx, int oldy);
	void DoRandomLines(ParticleType type);
	void UpdateVirtualPixel(int x, int y);
	void UpdateVirtualScreen();
	void clear();
};

} /* namespace sandcraft */

#endif /* PARTICLES_HPP_ */
