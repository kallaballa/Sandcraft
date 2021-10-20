#include "P2P.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <zlib.h>
#include "../../SandcraftServer/src/Message.hpp"
#include "Utils.hpp"
#include "GameState.hpp"


namespace sandcraft {

using namespace std;

bool startsWith(const string& haystack, const string& needle) {
	return needle.length() <= haystack.length()
			&& equal(needle.begin(), needle.end(), haystack.begin());
}

//FROM
//https://stackoverflow.com/a/34571089/5155484

typedef unsigned char uchar;
static const std::string b =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //=
static std::string base64_encode(const std::string &in) {
	std::string out;

	int val = 0, valb = -6;
	for (uchar c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back(b[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6)
		out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4)
		out.push_back('=');
	return out;
}

static std::string base64_decode(const std::string &in) {

	std::string out;

	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++)
		T[b[i]] = i;

	int val = 0, valb = -8;
	for (uchar c : in) {
		if (T[c] == -1)
			break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			out.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	return out;
}

EM_BOOL web_socket_open(int eventType, const EmscriptenWebSocketOpenEvent *e,
		void *userData) {
	using namespace scserver;
	printf("open(eventType=%d, userData=%ld)\n", eventType, (long) userData);
	Message m(LIST, { });
	std::stringstream ss;
	m.write(ss);
	emscripten_websocket_send_utf8_text(e->socket, ss.str().c_str());
//
//	char data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	emscripten_websocket_send_binary(e->socket, data, sizeof(data));
//
//	emscripten_websocket_close(e->socket, 0, 0);
	return 0;
}

EM_BOOL web_socket_close(int eventType, const EmscriptenWebSocketCloseEvent *e,
		void *userData) {
	printf(
			"close(eventType=%d, wasClean=%d, code=%d, reason=%s, userData=%ld)\n",
			eventType, e->wasClean, e->code, e->reason, (long) userData);
	return 0;
}

EM_BOOL web_socket_error(int eventType, const EmscriptenWebSocketErrorEvent *e,
		void *userData) {
	printf("error(eventType=%d, userData=%ld)\n", eventType, (long) userData);
	return 0;
}

std::vector<std::pair<string, string>> hostCandidate;
bool is_init = false;
EM_BOOL web_socket_message(int eventType,
		const EmscriptenWebSocketMessageEvent *e, void *userData) {
	using namespace scserver;
	printf(
			"message(eventType=%d, userData=%ld, data=%p, numBytes=%d, isText=%d)\n",
			eventType, (long) userData, e->data, e->numBytes, e->isText);

	if (e->isText) {
		printf("text data: \"%s\"\n", e->data);
		std::string str((const char*) e->data);
		if (startsWith(str, "Error:")) {
			std::cerr << str << std::endl;
			exit(1);
		} else if (startsWith(str, "list")) {
			auto lines = split(str, '\n');
			std::cerr << lines.size() << std::endl;
			assert(!lines.empty());
			bool found = false;
			std::string selSDP, selRoom;
			for (size_t i = 1; i < lines.size(); ++i) {
				auto tokens = split(lines[i], ' ');
				assert(tokens.size() == 4);
				string sdp = tokens[0];
				selSDP = base64_decode(sdp);
				selRoom = tokens[1];
				size_t max = stoi(tokens[2]);
				size_t participants = stoi(tokens[3]);
				if (participants < max) {
					P2P::rtc_->init(
							[=](Description desc) {
								GameState::getInstance().isHost_ = false;
								Message m(JOIN, {base64_encode(desc.operator string()), string("name-") + utils::random_id(32), selRoom});
								std::stringstream ss;
								m.write(ss);
								emscripten_websocket_send_utf8_text(e->socket, ss.str().c_str());
							},
							[=](Candidate candidate) {
								Message m(CLIENT, {base64_encode(candidate), base64_encode(candidate.mid())});
								std::stringstream ss;
								m.write(ss);
								std::cerr << "SEND CLIENT" << std::endl;
								emscripten_websocket_send_utf8_text(e->socket, ss.str().c_str());
							});
					found = true;
					break;
				}
			}

			if (!found) {
				P2P::rtc_->init(
						[=](Description desc) {
							GameState& gs = GameState::getInstance();
							if(gs.isHost_)
							return;
							gs.isHost_ = true;
							string sdp = base64_encode(desc);
							Message m(CREATE, {sdp, string("room-") + utils::random_id(32), "1"});
							std::stringstream ss;
							m.write(ss);
							emscripten_websocket_send_utf8_text(e->socket, ss.str().c_str());
						},
						[&](Candidate candidate) {
							std::cerr << "SET CANDIDATE" << std::endl;
							hostCandidate.push_back( {candidate, candidate.mid()});
						});
				if (!is_init) {
					P2P::rtc_->dc_ = P2P::rtc_->pc_->createDataChannel(
							"test");
				}
				is_init = true;
			} else {
				P2P::rtc_->answer(Description(selSDP, "answer"));
			}
		} else if (startsWith(str, "negotiate")) {
			for (auto& p : hostCandidate) {
				string cand = base64_encode(p.first);
				string mid = base64_encode(p.second);
				Message m(HOST, { cand, mid });
				std::stringstream ss;
				m.write(ss);
				emscripten_websocket_send_utf8_text(e->socket,
						ss.str().c_str());
				std::cerr << "SEND HOST:" << p.first << std::endl;
			}
			auto tokens = split(str, ' ');
			assert(tokens.size() == 4);
			string sdp = base64_decode(tokens[1]);
			P2P::rtc_->offer(Description(sdp, "offer"));
		} else if (startsWith(str, "client")) {
			auto tokens = split(str, ' ');
			assert(tokens.size() == 3);
			string cand = base64_decode(tokens[1]);
			string mid = base64_decode(tokens[2]);
			std::cerr << "add client" << cand << " " << mid << std::endl;
			P2P::rtc_->pc_->addRemoteCandidate(Candidate(cand, mid));
		} else if (startsWith(str, "host")) {
			auto tokens = split(str, ' ');
			assert(tokens.size() == 3);
			string cand = base64_decode(tokens[1]);
			string mid = base64_decode(tokens[2]);
			std::cerr << "add host" << cand << " " << mid << std::endl;
			P2P::rtc_->pc_->addRemoteCandidate(Candidate(cand, mid));
		}
	} else {
		printf("binary data:");
		for (int i = 0; i < e->numBytes; ++i)
			printf(" %02X", e->data[i]);
		printf("\n");

//		emscripten_websocket_delete(e->socket);
//		exit(0);
	}
	return 0;
}

WebRTC* P2P::rtc_ = nullptr;

P2P::P2P(string host, int port) {
	if (!emscripten_websocket_is_supported()) {
		printf("WebSockets are not supported, cannot continue!\n");
		exit(1);
	}

	EmscriptenWebSocketCreateAttributes attr;
	emscripten_websocket_init_create_attributes(&attr);

	attr.url = (std::string("wss://") + host + ":" + std::to_string(port)
			+ "/sandcraft").c_str();

	EMSCRIPTEN_WEBSOCKET_T socket = emscripten_websocket_new(&attr);
	if (socket <= 0) {
		printf("WebSocket creation failed, error code %d!\n",
				(EMSCRIPTEN_RESULT) socket);
		exit(1);
	}

	emscripten_websocket_set_onopen_callback(socket, (void* )42,
			web_socket_open);
	emscripten_websocket_set_onclose_callback(socket, (void* )43,
			web_socket_close);
	emscripten_websocket_set_onerror_callback(socket, (void* )44,
			web_socket_error);
	emscripten_websocket_set_onmessage_callback(socket, (void* )45,
			web_socket_message);
}

P2P::~P2P() {
	// TODO Auto-generated destructor stub
}

void P2P::initRTC(std::function<void(std::vector<byte>)> recvCallback) {
	rtc_ = new WebRTC(recvCallback);
}

void P2P::sendParticleRow(uint16_t y, Particles& particles) {
	Config& cfg = Config::getInstance();
	long inlen = cfg.width_ * sizeof(ParticleType);
	const char *inrow = (const char*) (particles.vs_ + (y * cfg.width_));
	static char *message = new char[inlen + 2];
	static char *compmsg = new char[inlen + 2];
	(*(uint16_t*) message) = y;
	memcpy(message + 2, inrow, inlen);

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in = (uInt)inlen + 2; // size of input, string + terminator
    defstream.next_in = (Bytef *)message; // input char array
    defstream.avail_out = (uInt)inlen + 2; // size of output
    defstream.next_out = (Bytef *)compmsg; // output char array

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_SPEED);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

//    std::cerr << inlen << ":" << strlen(compmsg) << std::endl;
	rtc_->dc_->send((byte*) compmsg, defstream.total_out);
}

void P2P::sendLine(int newX, int newY, int oldX, int oldY, ParticleType type, int penSize) {
	static uint16_t* msg = new uint16_t[6];
	msg[0] = newX;
	msg[1] = newY;
	msg[2] = oldX;
	msg[3] = oldY;
	msg[4] = (uint16_t) type;
	msg[5] = penSize;
//	std::cerr << "really:" << rtc_->dc_->isOpen() << std::endl;
	assert(rtc_->dc_->send((byte*) msg, 12));
}

} /* namespace scserver */
