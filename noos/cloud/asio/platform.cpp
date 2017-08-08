#include "platform.hpp"

namespace noos {
namespace cloud {

platform platform::operator()(json json_object)
{
    if (!json_object.empty()) {
        platform info = { json_object["platform"]["address"],
                          json_object["platform"]["port"],
                          json_object["platform"]["token"],
                          json_object["platform"]["user"],
                          json_object["platform"]["protocol"]};
        return info;
    }
    else {
        throw std::runtime_error("JSON used for platform data is empty");
    }
}

platform platform::operator()(std::string filename)
{
    std::ifstream f(filename.c_str());
    if(!f.good()) {
        throw std::runtime_error("Loading error: Configuration file " + filename + " not found");
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    f.close();
    return platform()(json::parse(buffer.str()));
}

}
}
