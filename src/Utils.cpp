#include "Utils.hpp"
#include <time.h>
#include <sstream>
#include <iomanip>

namespace sandcraft {

namespace {
static unsigned int s_rand_high = 1;
static unsigned int s_rand_low = 1 ^ 0x49616E42;
}

std::vector<std::string> utils::split(const std::string& s, const char& by) {
	std::stringstream ss(s);
	std::string t;
	std::vector<std::string> tokens;

	while (std::getline(ss, t, by))	{
		tokens.push_back(t);
	}
	return tokens;
}

std::string utils::int_to_hex_color(SDL_PixelFormat* format, uint32_t i) {
	uint8_t r, g, b;
	SDL_GetRGB(i, format, &r, &g, &b);
	std::stringstream stream;
	stream << "#" << std::setfill('0') << std::setw(2) << std::hex << (int) r
			<< std::setfill('0') << std::setw(2) << std::hex << (int) g
			<< std::setfill('0') << std::setw(2) << std::hex << (int) b;
	return stream.str();
}

void utils::srand(unsigned int seed) {
	s_rand_high = seed;
	s_rand_low = seed ^ 0x49616E42;
}

void utils::srand() {
	utils::srand(static_cast<unsigned int>(time(0)));
}

unsigned int utils::rand() {
	static const int shift = sizeof(int) / 2;
	s_rand_high = (s_rand_high >> shift) + (s_rand_high << shift);
	s_rand_high += s_rand_low;
	s_rand_low += s_rand_high;
	return s_rand_high;
}

std::string utils::random_id(size_t length) {
	using namespace std;
	static const string characters(
			"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	string id(length, '0');

	default_random_engine rng(random_device { }());
	uniform_int_distribution<int> dist(0, int(characters.size() - 1));
	generate(id.begin(), id.end(), [&]() {return characters.at(dist(rng));});
	return id;
}

size_t b64_encoded_size(size_t inlen)
{
	size_t ret;

	ret = inlen;
	if (inlen % 3 != 0)
		ret += 3 - (inlen % 3);
	ret /= 3;
	ret *= 4;

	return ret;
}

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* utils::b64_encode(const unsigned char *in, size_t len)
{
	char   *out;
	size_t  elen;
	size_t  i;
	size_t  j;
	size_t  v;

	if (in == NULL || len == 0)
		return NULL;

	elen = b64_encoded_size(len);
	out  = (char*)malloc(elen+1);
	out[elen] = '\0';

	for (i=0, j=0; i<len; i+=3, j+=4) {
		v = in[i];
		v = i+1 < len ? v << 8 | in[i+1] : v << 8;
		v = i+2 < len ? v << 8 | in[i+2] : v << 8;

		out[j]   = b64chars[(v >> 18) & 0x3F];
		out[j+1] = b64chars[(v >> 12) & 0x3F];
		if (i+1 < len) {
			out[j+2] = b64chars[(v >> 6) & 0x3F];
		} else {
			out[j+2] = '=';
		}
		if (i+2 < len) {
			out[j+3] = b64chars[v & 0x3F];
		} else {
			out[j+3] = '=';
		}
	}

	return out;
}

size_t utils::b64_decoded_size(const char *in)
{
	size_t len;
	size_t ret;
	size_t i;

	if (in == NULL)
		return 0;

	len = strlen(in);
	ret = len / 4 * 3;

	for (i=len; i-->0; ) {
		if (in[i] == '=') {
			ret--;
		} else {
			break;
		}
	}

	return ret;
}

int b64invs[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51 };


int b64_isvalidchar(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	if (c >= 'A' && c <= 'Z')
		return 1;
	if (c >= 'a' && c <= 'z')
		return 1;
	if (c == '+' || c == '/' || c == '=')
		return 1;
	return 0;
}

int utils::b64_decode(const char *in, unsigned char *out, size_t outlen)
{
	size_t len;
	size_t i;
	size_t j;
	int    v;

	if (in == NULL || out == NULL)
		return 0;

	len = strlen(in);
	if (outlen < b64_decoded_size(in) || len % 4 != 0)
		return 0;

	for (i=0; i<len; i++) {
		if (!b64_isvalidchar(in[i])) {
			return 0;
		}
	}

	for (i=0, j=0; i<len; i+=4, j+=3) {
		v = b64invs[in[i]-43];
		v = (v << 6) | b64invs[in[i+1]-43];
		v = in[i+2]=='=' ? v << 6 : (v << 6) | b64invs[in[i+2]-43];
		v = in[i+3]=='=' ? v << 6 : (v << 6) | b64invs[in[i+3]-43];

		out[j] = (v >> 16) & 0xFF;
		if (in[i+2] != '=')
			out[j+1] = (v >> 8) & 0xFF;
		if (in[i+3] != '=')
			out[j+2] = v & 0xFF;
	}

	return 1;
}




} /* namespace sandcraft */
