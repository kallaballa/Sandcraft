#include <cstdlib>
#include "GameState.hpp"
#include "Particles.hpp"

namespace sandcraft {

// Emitting a given particletype at (x,o) width pixels wide and
// with a p density (probability that a given pixel will be drawn
// at a given position withing the width)
void Particles::emit(int x, int width, ParticleType type, float p) {
	for (int i = x - width / 2; i < x + width / 2; i++) {
		if (utils::rand() < (int) (RAND_MAX * p))
			vs_[i + config_.width_] = type;
	}
}

//Performs logic of inert particles
void Particles::inertParticleLogic(int x, int y, ParticleType type) {
	int index, above, left, right, below, same, abovetwo;
	switch (type) {

		case NIL:
			above = x + ((y - 1) * config_.width_);
			left = (x + 1) + (y * config_.width_);
			right = (x - 1) + (y * config_.width_);
			below = x + ((y + 1) * config_.width_);
			if (vs_[above] != NOTHING)
				vs_[above] = NOTHING;
			if (vs_[below] != NOTHING)
				vs_[below] = NOTHING;
			if (vs_[left] != NOTHING)
				vs_[left] = NOTHING;
			if (vs_[right] != NOTHING)
				vs_[right] = NOTHING;
			break;
		case IRONWALL:
			above = x + ((y - 1) * config_.width_);
			left = (x + 1) + (y * config_.width_);
			right = (x - 1) + (y * config_.width_);
			if (utils::rand() % 200 == 0
					&& (vs_[above] == RUST || vs_[left] == RUST
							|| vs_[right] == RUST))
				vs_[x + (y * config_.width_)] = RUST;
			break;
		case TORCH:
			above = x + ((y - 1) * config_.width_);
			left = (x + 1) + (y * config_.width_);
			right = (x - 1) + (y * config_.width_);
			if (utils::rand() % 2 == 0) // Spawns fire
					{
				if (vs_[above] == NOTHING || vs_[above] == MOVEDFIRE) //Fire above
					vs_[above] = MOVEDFIRE;
				if (vs_[right] == NOTHING || vs_[right] == MOVEDFIRE) //Fire to the right
					vs_[right] = MOVEDFIRE;
				if (vs_[left] == NOTHING || vs_[left] == MOVEDFIRE) //Fire to the left
					vs_[left] = MOVEDFIRE;
			}
			if (vs_[above] == MOVEDWATER || vs_[above] == WATER) //Fire above
				vs_[above] = MOVEDSTEAM;
			if (vs_[right] == MOVEDWATER || vs_[right] == WATER) //Fire to the right
				vs_[right] = MOVEDSTEAM;
			if (vs_[left] == MOVEDWATER || vs_[left] == WATER) //Fire to the left
				vs_[left] = MOVEDSTEAM;

			break;
		case PLANT:
			if (utils::rand() % 2 == 0) //Making the plant grow slowly
					{
				index = 0;
				switch (utils::rand() % 4) {
					case 0:
						index = (x - 1) + (y * config_.width_);
						break;
					case 1:
						index = x + ((y - 1) * config_.width_);
						break;
					case 2:
						index = (x + 1) + (y * config_.width_);
						break;
					case 3:
						index = x + ((y + 1) * config_.width_);
						break;
				}
				if (vs_[index] == WATER)
					vs_[index] = PLANT;
			}
			break;
		case EMBER:
			below = x + ((y + 1) * config_.width_);
			if (vs_[below] == NOTHING || isBurnable(vs_[below]))
				vs_[below] = FIRE;

			index = 0;
			switch (utils::rand() % 4) {
				case 0:
					index = (x - 1) + (y * config_.width_);
					break;
				case 1:
					index = x + ((y - 1) * config_.width_);
					break;
				case 2:
					index = (x + 1) + (y * config_.width_);
					break;
				case 3:
					index = x + ((y + 1) * config_.width_);
					break;
			}
			if (vs_[index] == PLANT)
				vs_[index] = FIRE;

			if (utils::rand() % 18 == 0) // Making ember burn out slowly
				vs_[x + (y * config_.width_)] = NOTHING;
			break;
		case STOVE:
			above = x + ((y - 1) * config_.width_);
			abovetwo = x + ((y - 2) * config_.width_);
			if (utils::rand() % 4 == 0 && vs_[above] == WATER) // Boil the water
				vs_[above] = STEAM;
			if (utils::rand() % 4 == 0 && vs_[above] == SALTWATER) // Saltwater separates
					{
				vs_[above] = SALT;
				vs_[abovetwo] = STEAM;
			}
			if (utils::rand() % 8 == 0 && vs_[above] == OIL) // Set oil aflame
				vs_[above] = EMBER;
			break;
		case RUST:
			if (utils::rand() % 7000 == 0) //Deteriate rust
				vs_[x + (y * config_.width_)] = NOTHING;
			break;

			//####################### SPOUTS #######################
		case WATERSPOUT:
			if (utils::rand() % 6 == 0) // Take it easy on the spout
					{
				below = x + ((y + 1) * config_.width_);
				if (vs_[below] == NOTHING)
					vs_[below] = MOVEDWATER;
			}
			break;
		case SANDSPOUT:
			if (utils::rand() % 6 == 0) // Take it easy on the spout
					{
				below = x + ((y + 1) * config_.width_);
				if (vs_[below] == NOTHING)
					vs_[below] = MOVEDSAND;
			}
			break;
		case SALTSPOUT:
			if (utils::rand() % 6 == 0) // Take it easy on the spout
					{

				below = x + ((y + 1) * config_.width_);
				if (vs_[below] == NOTHING)
					vs_[below] = MOVEDSALT;
				if (vs_[below] == WATER || vs_[below] == MOVEDWATER)
					vs_[below] = MOVEDSALTWATER;
			}
			break;
		case OILSPOUT:
			if (utils::rand() % 6 == 0) // Take it easy on the spout
					{
				below = x + ((y + 1) * config_.width_);
				if (vs_[below] == NOTHING)
					vs_[below] = MOVEDOIL;
			}
			break;

		default:
			break;
	}

}

// Performing the movement logic of a given particle. The argument 'type'
// is passed so that we don't need a table lookup when determining the
// type to set the given particle to - i.e. if the particle is SAND then the
// passed type will be MOVEDSAND
inline void Particles::moveParticle(int x, int y, ParticleType type) {

	type = (ParticleType) (type + 1);

	int above = x + ((y - 1) * config_.width_);
	int same = x + (config_.width_ * y);
	int below = x + ((y + 1) * config_.width_);

	//If nothing below then just fall (gravity)
	if (!isFloating(type)) {
		if ((vs_[below] == NOTHING) && (utils::rand() % 8)) //utils::rand() % 8 makes it spread
				{
			vs_[below] = type;
			vs_[same] = NOTHING;
			return;
		}
	} else {
		if (utils::rand() % 3 == 0) //Slow down please
			return;

		//If nothing above then rise (floating - or reverse gravity? ;))
		if ((vs_[above] == NOTHING || vs_[above] == FIRE) && (utils::rand() % 8)
				&& (vs_[same] != ELEC) && (vs_[same] != MOVEDELEC)) //utils::rand() % 8 makes it spread
				{
			if (type == MOVEDFIRE && utils::rand() % 20 == 0)
				vs_[same] = NOTHING;
			else {
				vs_[above] = vs_[same];
				vs_[same] = NOTHING;
			}
			return;
		}

	}

	//Randomly select right or left first
	int sign = utils::rand() % 2 == 0 ? -1 : 1;

	// We'll only calculate these indicies once for optimization purpose
	int first = (x + sign) + (config_.width_ * y);
	int second = (x - sign) + (config_.width_ * y);

	int index = 0;
	//Particle type specific logic
	switch (type) {
		case MOVEDELEC:
			if (utils::rand() % 2 == 0)
				vs_[same] = NOTHING;
			break;
		case MOVEDSTEAM:
			if (utils::rand() % 1000 == 0) {
				vs_[same] = MOVEDWATER;
				return;
			}
			if (utils::rand() % 500 == 0) {
				vs_[same] = NOTHING;
				return;
			}
			if (!isInert(vs_[above]) && !isFloating(vs_[above])) {
				if (utils::rand() % 15 == 0) {
					vs_[same] = NOTHING;
					return;
				} else {
					vs_[same] = vs_[above];
					vs_[above] = MOVEDSTEAM;
					return;
				}
			}
			break;
		case MOVEDFIRE:

			if (!isBurnable(vs_[above]) && utils::rand() % 10 == 0) {
				vs_[same] = NOTHING;
				return;
			}

			// Let the snowman melt!
			if (utils::rand() % 4 == 0) {
				if (vs_[above] == ICE) {
					vs_[above] = WATER;
					vs_[same] = NOTHING;
				}
				if (vs_[below] == ICE) {
					vs_[below] = WATER;
					vs_[same] = NOTHING;
				}
				if (vs_[first] == ICE) {
					vs_[first] = WATER;
					vs_[same] = NOTHING;
				}
				if (vs_[second] == ICE) {
					vs_[second] = WATER;
					vs_[same] = NOTHING;
				}
			}

			//Let's burn whatever we can!
			index = 0;
			switch (utils::rand() % 4) {
				case 0:
					index = above;
					break;
				case 1:
					index = below;
					break;
				case 2:
					index = first;
					break;
				case 3:
					index = second;
					break;
			}
			if (isBurnable(vs_[index])) {
				if (burnsAsEmber(vs_[index]))
					vs_[index] = EMBER;
				else
					vs_[index] = FIRE;
			}
			break;
		case MOVEDWATER:
			if (utils::rand() % 200 == 0 && vs_[below] == IRONWALL)
				vs_[below] = RUST;

			if (vs_[below] == FIRE || vs_[above] == FIRE || vs_[first] == FIRE
					|| vs_[second] == FIRE)
				vs_[same] = MOVEDSTEAM;

			//Making water+dirt into dirt
			if (vs_[below] == DIRT) {
				vs_[below] = MOVEDMUD;
				vs_[same] = NOTHING;
			}
			if (vs_[above] == DIRT) {
				vs_[above] = MOVEDMUD;
				vs_[same] = NOTHING;
			}

			//Making water+salt into saltwater
			if (vs_[above] == SALT || vs_[above] == MOVEDSALT) {
				vs_[above] = MOVEDSALTWATER;
				vs_[same] = NOTHING;
			}
			if (vs_[below] == SALT || vs_[below] == MOVEDSALT) {
				vs_[below] = MOVEDSALTWATER;
				vs_[same] = NOTHING;
			}

			if (utils::rand() % 60 == 0) //Melting ice
					{
				switch (utils::rand() % 4) {
					case 0:
						index = above;
						break;
					case 1:
						index = below;
						break;
					case 2:
						index = first;
						break;
					case 3:
						index = second;
						break;
				}
				if (vs_[index] == ICE)
					vs_[index] = WATER; //--
			}
			break;
		case MOVEDACID:
			switch (utils::rand() % 4) {
				case 0:
					index = above;
					break;
				case 1:
					index = below;
					break;
				case 2:
					index = first;
					break;
				case 3:
					index = second;
					break;
			}
			if (vs_[index] != WALL && vs_[index] != IRONWALL
					&& vs_[index] != WATER && vs_[index] != MOVEDWATER
					&& vs_[index] != ACID && vs_[index] != MOVEDACID)
				vs_[index] = NOTHING;
			break;
			break;
		case MOVEDSALT:
			if (utils::rand() % 20 == 0) {
				switch (utils::rand() % 4) {
					case 0:
						index = above;
						break;
					case 1:
						index = below;
						break;
					case 2:
						index = first;
						break;
					case 3:
						index = second;
						break;
				}
				if (vs_[index] == ICE)
					vs_[index] = WATER; //--
			}
			break;
		case MOVEDSALTWATER:
			//Saltwater separated by heat
			//	if (vs_[above] == FIRE || vs_[below] == FIRE || vs_[first] == FIRE || vs_[second] == FIRE || vs_[above] == STOVE || vs_[below] == STOVE || vs_[first] == STOVE || vs_[second] == STOVE)
			//	{
			//		vs_[same] = SALT;
			//		vs_[above] = STEAM;
			//	}
			if (utils::rand() % 40 == 0) //Saltwater dissolves ice more slowly than pure salt
					{
				switch (utils::rand() % 4) {
					case 0:
						index = above;
						break;
					case 1:
						index = below;
						break;
					case 2:
						index = first;
						break;
					case 3:
						index = second;
						break;
				}
				if (vs_[index] == ICE)
					vs_[index] = WATER;
			}
			break;
		case MOVEDOIL:
			switch (utils::rand() % 4) {
				case 0:
					index = above;
					break;
				case 1:
					index = below;
					break;
				case 2:
					index = first;
					break;
				case 3:
					index = second;
					break;
			}
			if (vs_[index] == FIRE)
				vs_[same] = FIRE;
			break;

		default:
			break;
	}

	//Peform 'realism' logic?
	// When adding dynamics to this part please use the following structure:
	// If a particle A is ligther than particle B then add vs_[above] == B to the condition in case A (case MOVED_A)
	if (config_.implementParticleSwaps_) {
		switch (type) {
			case MOVEDWATER:
				if (vs_[above] == SAND || vs_[above] == MUD
						|| vs_[above] == SALTWATER && utils::rand() % 3 == 0) {
					vs_[same] = vs_[above];
					vs_[above] = type;
					return;
				}
				break;
			case MOVEDOIL:
				if (vs_[above] == WATER && utils::rand() % 3 == 0) {
					vs_[same] = vs_[above];
					vs_[above] = type;
					return;
				}
				break;
			case MOVEDSALTWATER:
				if (vs_[above] == DIRT || vs_[above] == MUD
						|| vs_[above] == SAND && utils::rand() % 3 == 0) {
					vs_[same] = vs_[above];
					vs_[above] = type;
					return;
				}
				break;

			default:
				break;
		}
	}

	// The place below (x,y+1) is filled with something, then check (x+sign,y+1) and (x-sign,y+1)
	// We chose sign randomly to randomly check eigther left or right
	// This is for elements that fall downward
	if (!isFloating(type)) {
		int firstdown = (x + sign) + ((y + 1) * config_.width_);
		int seconddown = (x - sign) + ((y + 1) * config_.width_);

		if (vs_[firstdown] == NOTHING) {
			vs_[firstdown] = type;
			vs_[same] = NOTHING;
		} else if (vs_[seconddown] == NOTHING) {
			vs_[seconddown] = type;
			vs_[same] = NOTHING;
		}
		//If (x+sign,y+1) is filled then try (x+sign,y) and (x-sign,y)
		else if (vs_[first] == NOTHING) {
			vs_[first] = type;
			vs_[same] = NOTHING;
		} else if (vs_[second] == NOTHING) {
			vs_[second] = type;
			vs_[same] = NOTHING;
		}
	}
	// Make steam move
	else if (type == MOVEDSTEAM) {
		int firstup = (x + sign) + ((y - 1) * config_.width_);
		int secondup = (x - sign) + ((y - 1) * config_.width_);

		if (vs_[firstup] == NOTHING) {
			vs_[firstup] = type;
			vs_[same] = NOTHING;
		} else if (vs_[secondup] == NOTHING) {
			vs_[secondup] = type;
			vs_[same] = NOTHING;
		}
		//If (x+sign,y+1) is filled then try (x+sign,y) and (x-sign,y)
		else if (vs_[first] == NOTHING) {
			vs_[first] = type;
			vs_[same] = NOTHING;
		} else if (vs_[second] == NOTHING) {
			vs_[second] = type;
			vs_[same] = NOTHING;
		}
	}
}

//Drawing a filled circle at a given position with a given radius and a given partice type
void Particles::drawParticles(int xpos, int ypos, int radius,
		ParticleType type) {
	for (int x = ((xpos - radius - 1) < 0) ? 0 : (xpos - radius - 1);
			x <= xpos + radius && x < config_.width_; x++)
		for (int y = ((ypos - radius - 1) < 0) ? 0 : (ypos - radius - 1);
				y <= ypos + radius && y < config_.height_; y++) {
			if ((x - xpos) * (x - xpos) + (y - ypos) * (y - ypos)
					<= radius * radius)
				vs_[x + (config_.width_ * y)] = type;
		};
}

// Drawing a line
void Particles::drawLine(int newx, int newy, int oldx, int oldy) {
	drawLineCallback_(newx, newy, oldx, oldy, currentParticleType_);
//	if (GameState::getInstance().isHost)
		drawLine(newx, newy, oldx, oldy, currentParticleType_, GameState::getInstance().penSize_);
}

void Particles::drawLine(int newx, int newy, int oldx, int oldy,
		ParticleType type, int penSize) {
	if (newx == oldx && newy == oldy) {
		drawParticles(newx, newy, penSize, type);
	} else {
		float step = 1.0f
				/ ((abs(newx - oldx) > abs(newy - oldy)) ?
						abs(newx - oldx) : abs(newy - oldy));
		for (float a = 0; a < 1; a += step)
			drawParticles(a * newx + (1 - a) * oldx, a * newy + (1 - a) * oldy,
					penSize, type);
	}
}

// Drawing some random lines
void Particles::doRandomLines(ParticleType type) {
	ParticleType tmp = currentParticleType_;
	currentParticleType_ = type;
	for (int i = 0; i < 20; i++) {
		int x1 = utils::rand() % config_.width_;
		int x2 = utils::rand() % config_.width_;

		drawLine(x1, 0, x2, config_.height_, currentParticleType_, gs_.penSize_);
	}

	for (int i = 0; i < 20; i++) {
		int y1 = utils::rand() % config_.height_;
		int y2 = utils::rand() % config_.height_;

		drawLine(0, y1, config_.width_, y2, currentParticleType_, gs_.penSize_);
	}
	currentParticleType_ = tmp;
}

// Updating a virtual pixel
void Particles::updateVirtualPixel(int x, int y) {
	ParticleType same = vs_[x + (config_.width_ * y)];
	if (same != NOTHING) {
		if (isInert(same))
			inertParticleLogic(x, y, same);
		else if (utils::rand() >= RAND_MAX / 13 && same % 2 == 0)
			moveParticle(x, y, same); //THe rand condition makes the particles fall unevenly
	}

}

// Updating the particle system (virtual screen) pixel by pixel
void Particles::updateVirtualScreen() {
	auto l = lock();
	for (int y = 0; y < config_.height_ - config_.dboard_height_; y++) {
		// Due to biasing when iterating through the scanline from left to right,
		// we now chose our direction randomly per scanline.
		if (utils::rand() % 2 == 0)
 			for (int x = config_.width_ - 2; x--;)
				updateVirtualPixel(x, y);
		else
			for (int x = 1; x < config_.width_ - 1; x++)
				updateVirtualPixel(x, y);
	}
}

void Particles::logic() {
	Config& cfg = Config::getInstance();
	GameState& gs = GameState::getInstance();
	//To emit or not to emit
	if (gs.emitWater_)
		emit((cfg.width_ / 2 - ((cfg.width_ / 6) * 2)), 20, WATER,
				gs.waterDens_);
	if (gs.emitSand_)
		emit((cfg.width_ / 2 - (cfg.width_ / 6)), 20, SAND, gs.sandDens_);
	if (gs.emitSalt_)
		emit((cfg.width_ / 2 + (cfg.width_ / 6)), 20, SALT, gs.saltDens_);
	if (gs.emitOil_)
		emit((cfg.width_ / 2 + ((cfg.width_ / 6) * 2)), 20, OIL, gs.oilDens_);
	//If the button is pressed (and no event has occured since last frame due
	// to the polling procedure, then draw at the position (enabeling 'dynamic emitters')
	if (gs.mouse_down_) {
//		std::cout << "point" << std::endl;
		drawLine(gs.oldx_, gs.oldy_, gs.oldx_, gs.oldy_, currentParticleType_, gs_.penSize_);
	}

	{
		std::unique_lock<std::mutex>(levmtx_);
		while(!lineQ_.empty()) {
			auto& lev = lineQ_.front();
//			std::cout << "lev" << std::endl;
			drawLine(lev.newX_, lev.newY_,lev.oldX_, lev.oldY_);
			lineQ_.pop();
		}
	}
	//Clear bottom line
	for (int i = 0; i < cfg.width_; i++)
		(*this)[i + ((cfg.height_ - cfg.dboard_height_ - 1) * cfg.width_)] =
				NOTHING;
	//Clear top line
	for (int i = 0; i < cfg.width_; i++)
		(*this)[i + ((0) * cfg.width_)] = NOTHING;

	updateVirtualScreen();
}

//Cearing the particle system
void Particles::clear() {
	for (int w = 0; w < config_.width_; w++) {
		for (int h = 0; h < config_.height_; h++) {
			vs_[w + (config_.width_ * h)] = NOTHING;
		}
	}
}
} /* namespace sandcraft */
