#ifndef SRC_WEBSOCKETCLIENT_HPP_
#define SRC_WEBSOCKETCLIENT_HPP_

#include <string>
#include <emscripten/websocket.h>
#include "WebRTC.hpp"

namespace sandcraft {

class WebsocketClient {
public:
	static bool is_host_;
	static WebRTC* rtc_;
	WebsocketClient(int port, WebRTC* rtc);
	virtual ~WebsocketClient();
};

} /* namespace scserver */

#endif /* SRC_WEBSOCKETCLIENT_HPP_ */
