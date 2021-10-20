#ifndef SRC_P2P_HPP_
#define SRC_P2P_HPP_

#include <string>
#include <emscripten/websocket.h>
#include "WebRTC.hpp"
#include "Particles.hpp"

namespace sandcraft {

class P2P {
public:
	static bool isClosed_;
	static WebRTC* rtc_;
	static EMSCRIPTEN_WEBSOCKET_T socket_;

	P2P(string host, int port);
	virtual ~P2P();
	void initRTC(std::function<void(std::vector<byte>)> recvCallback);
	void sendParticleRow(uint16_t y, Particles& particles);
	void sendLine(int newX, int newY, int oldX, int oldY, ParticleType type, int penSize);

	bool isClosed() {
		return isClosed_ || (rtc_ != nullptr && rtc_->isClosed());
	}

	bool isOpen() {
		return !isClosed() && rtc_ != nullptr && rtc_->isOpen();
	}

};

} /* namespace scserver */

#endif /* SRC_P2P_HPP_ */
