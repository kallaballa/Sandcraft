/*
 * WebRTC.cpp
 *
 *  Created on: Oct 15, 2021
 *      Author: elchaschab
 */

#include "WebRTC.hpp"

namespace sandcraft {

void descCB(Description desc) {
	std::cerr << "desc" << std::endl;
}

void candCB(Candidate cand) {
	std::cerr << "cand" << std::endl;
}
} /* namespace sandcraft */
