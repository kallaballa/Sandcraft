#include "Nexus.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <zlib.h>
#include "../../SandcraftServer/src/Message.hpp"
#include "Utils.hpp"
#include "GameState.hpp"
#include "Logger.hpp"

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
	emscripten_websocket_send_utf8_text(e->socket, Message(LIST, {}).str().c_str());
//
//	char data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	emscripten_websocket_send_binary(e->socket, data, sizeof(data));
//
//	emscripten_websocket_close(e->socket, 0, 0);
	return 0;
}

EM_BOOL web_socket_close(int eventType, const EmscriptenWebSocketCloseEvent *e,
		void *userData) {

	if(Nexus::socket_ > 0)  {
		Nexus::isClosed_ = true;

	printf(
			"close(eventType=%d, wasClean=%d, code=%d, reason=%s, userData=%ld)\n",
			eventType, e->wasClean, e->code, e->reason, (long) userData);
	}
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
			log_error("Received error", str);
			exit(1);
		} else if (startsWith(str, "list")) {
			auto lines = split(str, '\n');
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
					Nexus::rtc_->init(
							[=](Description desc) {
								GameState::getInstance().isHost_ = false;
								Message m(JOIN, {base64_encode(desc.operator string()), string("name-") + utils::random_id(32), selRoom});
								emscripten_websocket_send_utf8_text(e->socket, m.str().c_str());
							},
							[=](Candidate candidate) {
								Message m(CLIENT, {base64_encode(candidate), base64_encode(candidate.mid())});
								log_info("send client candidate", candidate);
								emscripten_websocket_send_utf8_text(e->socket, m.str().c_str());
							});
					found = true;
					break;
				}
			}

			if (!found) {
				Nexus::rtc_->init(
						[=](Description desc) {
							GameState& gs = GameState::getInstance();
							if(gs.isHost_)
							return;
							gs.isHost_ = true;
							string sdp = base64_encode(desc);
							Message m(CREATE, {sdp, string("room-") + utils::random_id(32), "1"});
							emscripten_websocket_send_utf8_text(e->socket, m.str().c_str());
						},
						[&](Candidate candidate) {
							log_info("add local candidate", candidate);
							hostCandidate.push_back( {candidate, candidate.mid()});
						});
				if (!is_init) {
					Nexus::rtc_->dc_ = Nexus::rtc_->pc_->createDataChannel(
							"test");
				}
				is_init = true;
			} else {
				Nexus::rtc_->answer(Description(selSDP, "answer"));
			}
		} else if (startsWith(str, "negotiate")) {
			for (auto& p : hostCandidate) {
				string cand = base64_encode(p.first);
				string mid = base64_encode(p.second);
				Message m(HOST, { cand, mid });
				emscripten_websocket_send_utf8_text(e->socket,
						m.str().c_str());
				log_info("send host candidate", p.first);
			}
			auto tokens = split(str, ' ');
			assert(tokens.size() == 4);
			string sdp = base64_decode(tokens[1]);
			Nexus::rtc_->offer(Description(sdp, "offer"));
		} else if (startsWith(str, "client")) {
			auto tokens = split(str, ' ');
			assert(tokens.size() == 3);
			string cand = base64_decode(tokens[1]);
			string mid = base64_decode(tokens[2]);
			log_info("add remote candidate (client)", cand);
			Nexus::rtc_->pc_->addRemoteCandidate(Candidate(cand, mid));
		} else if (startsWith(str, "host")) {
			auto tokens = split(str, ' ');
			assert(tokens.size() == 3);
			string cand = base64_decode(tokens[1]);
			string mid = base64_decode(tokens[2]);
			log_info("add remote candidate (host)", cand);
			Nexus::rtc_->pc_->addRemoteCandidate(Candidate(cand, mid));
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

WebRTC* Nexus::rtc_ = nullptr;
bool Nexus::isClosed_ = false;
EMSCRIPTEN_WEBSOCKET_T Nexus::socket_ = 0;

Nexus::Nexus(string host, int port) {
	rtc_ = nullptr;
	isClosed_ = false;
	socket_ = 0;

	if (!emscripten_websocket_is_supported()) {
		printf("WebSockets are not supported, cannot continue!\n");
		exit(1);
	}

	EmscriptenWebSocketCreateAttributes attr;
	emscripten_websocket_init_create_attributes(&attr);

	string url = (std::string("wss://") + host + ":" + std::to_string(port)
	+ "/sandcraft");
	attr.url = url.c_str();

	socket_ = emscripten_websocket_new(&attr);
	if (socket_ <= 0) {
		printf("WebSocket creation failed, error code %d!\n",
				(EMSCRIPTEN_RESULT) socket_);
		exit(1);
	}

	emscripten_websocket_set_onopen_callback(socket_, (void* )42,
			web_socket_open);
	emscripten_websocket_set_onclose_callback(socket_, (void* )43,
			web_socket_close);
	emscripten_websocket_set_onerror_callback(socket_, (void* )44,
			web_socket_error);
	emscripten_websocket_set_onmessage_callback(socket_, (void* )45,
			web_socket_message);
}

Nexus::~Nexus() {
	if(socket_ > 0) {
		EMSCRIPTEN_WEBSOCKET_T copy = socket_;
		socket_ = 0;
		emscripten_websocket_delete(copy);
	}
	if(rtc_ != nullptr)
		delete rtc_;
}

void Nexus::initRTC(std::function<void(std::vector<byte>)> recvCallback) {
	rtc_ = new WebRTC(recvCallback);
}

void Nexus::sendParticles(Particles& particles) {
	Config& cfg = Config::getInstance();
	long inlen = cfg.width_ * cfg.height_ * sizeof(ParticleType);
	const char *inrow = (const char*) particles.vs_;
	static char *message = new char[inlen + 2];
	static char *compmsg = new char[inlen + 2];
	(*(int16_t*) message) = -1;
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

	rtc_->dc_->send((byte*) compmsg, defstream.total_out);
}

void Nexus::sendParticleRow(uint16_t y, Particles& particles) {
	Config& cfg = Config::getInstance();
	long inlen = cfg.width_ * sizeof(ParticleType);
	const char *inrow = (const char*) (particles.vs_ + (y * cfg.width_));
	static char *message = new char[inlen + 2];
	static char *compmsg = new char[inlen + 2];
	(*(int16_t*) message) = y;
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

	rtc_->dc_->send((byte*) compmsg, defstream.total_out);
}

void Nexus::receiveParticles(const std::vector<byte>& data, Particles* particles) {
	Config& cfg = Config::getInstance();
	const char* msgdata = (const char*)data.data();
	long decompLen = sizeof(ParticleType) * cfg.width_ * cfg.height_ + 2;
	static char* decomp = new char[decompLen];

	z_stream infstream;
	z_stream defstream;
	infstream.zalloc = Z_NULL;
	infstream.zfree = Z_NULL;
	infstream.opaque = Z_NULL;
	// setup "b" as the input and "c" as the compressed output
	infstream.avail_in = (uInt)data.size();
	infstream.next_in = (Bytef *)msgdata;// input char array
	infstream.avail_out = (uInt)decompLen;// size of output
	infstream.next_out = (Bytef *)decomp;// output char array
	inflateInit(&infstream);
	inflate(&infstream, Z_NO_FLUSH);
	inflateEnd(&infstream);
//						    std::cerr << strlen(msgdata) << ":" << decompLen << std::endl;
	int16_t y = (*(int16_t*)decomp);
	assert(y == -1);
	memcpy(particles->vs_, decomp + 2, decompLen - 2);
}

void Nexus::receiveParticleRow(const std::vector<byte>& data, Particles* particles) {
	Config& cfg = Config::getInstance();
	const char* msgdata = (const char*)data.data();
	long decompLen = sizeof(ParticleType) * cfg.width_ + 2;
	static char* decomp = new char[decompLen];

	z_stream infstream;
	z_stream defstream;
	infstream.zalloc = Z_NULL;
	infstream.zfree = Z_NULL;
	infstream.opaque = Z_NULL;
	// setup "b" as the input and "c" as the compressed output
	infstream.avail_in = (uInt)data.size();
	infstream.next_in = (Bytef *)msgdata;// input char array
	infstream.avail_out = (uInt)decompLen;// size of output
	infstream.next_out = (Bytef *)decomp;// output char array
	inflateInit(&infstream);
	inflate(&infstream, Z_NO_FLUSH);
	inflateEnd(&infstream);
//						    std::cerr << strlen(msgdata) << ":" << decompLen << std::endl;
	int16_t y = (*(int16_t*)decomp);
	memcpy(particles->vs_ + (cfg.width_ * y), decomp + 2, decompLen - 2);
}

void Nexus::sendDrawLine(int newX, int newY, int oldX, int oldY, ParticleType type, int penSize) {
	static uint16_t* msg = new uint16_t[6];
	msg[0] = newX;
	msg[1] = newY;
	msg[2] = oldX;
	msg[3] = oldY;
	msg[4] = (uint16_t) type;
	msg[5] = penSize;
	assert(rtc_->dc_->send((byte*) msg, 12));
}

void Nexus::receiveDrawLine(const std::vector<byte>& data, Particles* particles) {
	assert(data.size() == 12);
	const uint16_t* msgdata = (const uint16_t*)data.data();
	if(particles != nullptr) {
		particles->drawLine(msgdata[0], msgdata[1], msgdata[2], msgdata[3],(ParticleType)msgdata[4], msgdata[5]);
	}
}
} /* namespace scserver */
