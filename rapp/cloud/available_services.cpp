#include "available_services.hpp"

namespace rapp {
namespace cloud {

available_services::available_services(std::function<void(std::vector<service>)> callback)
: http_request("GET /available_services HTTP/1.1\r\n"),
  delegate_(callback)
{
    assert(callback);
}

void available_services::deserialise(std::string json) 
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            std::vector<service> services;
            for (auto it_s : json_f["services"]) {
                services.push_back(std::make_pair(misc::get_json_value<std::string>("name", it_s), 
                                                  misc::get_json_value<std::string>("url", it_s)));
            }
            delegate_(services);
        }
    }
}

}
}
