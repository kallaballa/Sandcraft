#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <cstddef>
#include <cassert>
#include "Utils.hpp"

namespace sandcraft {

class Config {
private:
	static Config* instance_;
	Config() {}
public:
	size_t width_ = 0;
	size_t height_ = 0;
	size_t btn_size_ = 20;
	int btn_upper_row_y_ = 0;
	int btn_middle_row_y_ = 0;
	int btn_lower_row_y_ = 0;
	size_t dboard_height_ = 0;

	//Init and declare ParticleSwapping
	bool implementParticleSwaps_ = true;


	static Config& getInstance() {
		if(instance_ == nullptr)
			instance_ = new Config();
		return *instance_;
	}
};

} /* namespace sandcraft */

#endif /* CONFIG_HPP_ */
