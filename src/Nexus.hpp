#ifndef SRC_NEXUS_HPP_
#define SRC_NEXUS_HPP_

#include <string>
#include <emscripten/websocket.h>
#include "WebRTC.hpp"
#include "Particles.hpp"

namespace sandcraft {

class Nexus {
public:
	static bool isClosed_;
	static WebRTC* rtc_;
	static EMSCRIPTEN_WEBSOCKET_T socket_;

	Nexus(string host, int port);
	virtual ~Nexus();
	void initRTC(std::function<void(std::vector<byte>)> recvCallback);
	void receiveParticles(const std::vector<byte>& data, Particles* particles);
	void sendParticles(Particles& particles);
	void sendParticleRow(uint16_t y, Particles& particles);
	void receiveParticleRow(const std::vector<byte>& data, Particles* particles);
	void sendDrawLine(int newX, int newY, int oldX, int oldY, ParticleType type, int penSize);
	void receiveDrawLine(const std::vector<byte>& data, Particles* particles);

	bool isClosed() {
		return isClosed_ || (rtc_ != nullptr && rtc_->isClosed());
	}

	bool isOpen() {
		return !isClosed() && rtc_ != nullptr && rtc_->isOpen();
	}

};

} /* namespace scserver */

#endif /* SRC_NEXUS_HPP_ */
