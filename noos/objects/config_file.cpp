#include "config_file.hpp"

namespace noos {
namespace object {

config_file::config_file(const std::string filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open()) {
		throw std::runtime_error("Error: failed to open " + filepath);
	} else {
        std::vector<char> v((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));
        std::string tmp(v.begin(), v.end());
        data__ = tmp;
        file.close();
    }
}

std::string config_file::get_data()
{
    return data__;
}

}
}
