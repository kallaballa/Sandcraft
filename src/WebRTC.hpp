#ifndef SRC_WEBRTC_HPP_
#define SRC_WEBRTC_HPP_

#include "rtc/rtc.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <functional>

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
//		config_.iceServers.emplace_back("stun:stun.l.google.com:19302");
		std::cerr << "INIT: " << std::endl;
		pc_ = std::make_shared<PeerConnection>(config_);

		pc_->onLocalDescription([=](Description description) {
			std::cerr << "local desc" << std::endl;
			cbDesc(description);
		});
		pc_->onLocalCandidate([=](Candidate candidate) {
			std::cerr << "local candidate" << std::endl;
			cbCand(candidate);
		});

		pc_->onStateChange(
		    [&](PeerConnection::State state) {
			cout << "[State: " << (int)state << "]" << endl;
			if((int)state > 2)
				isClosed_ = true;
		});
		pc_->onGatheringStateChange([](PeerConnection::GatheringState state) {
			cout << "[Gathering State: " << (int)state << "]" << endl;
		});
	}

	void answer(const Description& desc) {
		string sdp = desc.operator std::string();
		std::cerr << "ANSWER: " << std::endl;

		pc_->onDataChannel([&](shared_ptr<DataChannel> _dc) {
			isOpen_ = false;

			cout << "[Got a DataChannel with label: " << _dc->label() << "]" << endl;
			dc_ = _dc;

			dc_->onOpen([&]() {
				cout << "[DataChannel open: " << dc_->label() << "]" << endl;
				isOpen_ = true;
			});

			dc_->onClosed([&]() {
				cout << "[DataChannel closed: " << dc_->label() << "]" << endl;
				isOpen_ = false;
				isClosed_ = true;
			});

			dc_->onMessage([&](variant<binary, string> message) {
				if (holds_alternative<binary>(message)) {
					cbMsg_(get<binary>(message));
				}
			});
		});

		pc_->setRemoteDescription(Description(sdp, "offer"));
	}

	void offer(const Description& desc) {
		string sdp = desc.operator std::string();
		std::cerr << "OFFER: " << std::endl;
		dc_->onOpen([&]() {
			cout << "[DataChannel open: " << dc_->label() << "]" << endl;
			isOpen_ = true;
		});

		dc_->onClosed([&]() {
			cout << "[DataChannel closed: " << dc_->label() << "]" << endl;
			isOpen_ = false;
			isClosed_ = true;
		});

		dc_->onMessage([&](variant<binary, string> message) {
			if (holds_alternative<binary>(message)) {
				cbMsg_(get<binary>(message));
			}
		});
		pc_->setRemoteDescription(Description(sdp, "answer"));
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
