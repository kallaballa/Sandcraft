#ifndef SRC_WEBRTC_HPP_
#define SRC_WEBRTC_HPP_

#include "rtc/rtc.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <functional>
#include "Logger.hpp"

using namespace rtc;
using namespace std;

template <class T> weak_ptr<T> make_weak_ptr(shared_ptr<T> ptr) { return ptr; }

namespace sandcraft {

class WebRTC {
private:
	Configuration config_;
	std::function<void(std::vector<byte>)> cbMsg_;
	bool isOpen_ = false;
	bool isClosed_ = false;
public:
	shared_ptr<DataChannel> dc_ = nullptr;
	shared_ptr<PeerConnection> pc_ = nullptr;

	void init(std::function<void(Description)> cbDesc, std::function<void(Candidate)> cbCand) {
		config_.iceServers.emplace_back("stun:stun.l.google.com:19302");
		pc_ = std::make_shared<PeerConnection>(config_);

		pc_->onLocalDescription([=](Description description) {
			log_info("local description", description);
			cbDesc(description);
		});
		pc_->onLocalCandidate([=](Candidate candidate) {
			log_info("local candidate", candidate);
			cbCand(candidate);
		});

		pc_->onStateChange(
		    [&](PeerConnection::State state) {
			log_info("PeerConnection state", std::to_string((int) state));
			if((int)state > 2)
				isClosed_ = true;
		});
		pc_->onGatheringStateChange([](PeerConnection::GatheringState state) {
			log_info("Gathering state", std::to_string((int) state));
		});
	}

	void answer(const Description& desc) {
		log_debug("answer", desc);

		pc_->onDataChannel([&](shared_ptr<DataChannel> _dc) {
			isOpen_ = false;

			log_info("Got DataChannel", _dc->label());
			dc_ = _dc;

			dc_->onOpen([&]() {
				log_info("DataChannel open", dc_->label());
				isOpen_ = true;
			});

			dc_->onClosed([&]() {
				log_info("DataChannel closed", dc_->label());
				isOpen_ = false;
				isClosed_ = true;
			});

			dc_->onMessage([&](variant<binary, string> message) {
				if (holds_alternative<binary>(message)) {
					cbMsg_(get<binary>(message));
				}
			});
		});

		pc_->setRemoteDescription(Description(desc, "offer"));
	}

	void offer(const Description& desc) {
		log_debug("offer", desc);
		dc_->onOpen([&]() {
			log_info("DataChannel open", dc_->label());
			isOpen_ = true;
		});

		dc_->onClosed([&]() {
			log_info("DataChannel closed", dc_->label());
			isOpen_ = false;
			isClosed_ = true;
		});

		dc_->onMessage([&](variant<binary, string> message) {
			if (holds_alternative<binary>(message)) {
				cbMsg_(get<binary>(message));
			}
		});
		pc_->setRemoteDescription(Description(desc, "answer"));
	}

public:
	WebRTC(std::function<void(std::vector<byte>)> cbMsg) : cbMsg_(cbMsg) {
	}
	virtual ~WebRTC() {

	}

	bool isOpen() {
		return isOpen_ && dc_->isOpen();
	}

	bool isClosed() {
		return isClosed_;
	}
};

} /* namespace sandcraft */

#endif /* SRC_WEBRTC_HPP_ */
