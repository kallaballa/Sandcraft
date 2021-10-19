#ifndef SRC_P2P_HPP_
#define SRC_P2P_HPP_

#include <string>
#include <emscripten/websocket.h>
#include "WebRTC.hpp"
#include "Particles.hpp"

namespace sandcraft {

class P2P {
public:
	static WebRTC* rtc_;


	P2P(string host, int port);
	virtual ~P2P();
	void initRTC(std::function<void(std::vector<byte>)> recvCallback);
	void sendParticleRow(uint16_t y, Particles& particles);
	void sendLine(int newX, int newY, int oldX, int oldY, ParticleType type, int penSize);

	bool isOpen() {
		return rtc_ != nullptr && rtc_->isOpen();
	}

};

} /* namespace scserver */

#endif /* SRC_P2P_HPP_ */
