#include "vision_batch.hpp"

namespace rapp
{
namespace cloud
{

const std::string vision_batch::uri__ = "POST /vision_batch HTTP/1.1\r\n";

vision_batch::vision_batch(const rapp::object::picture & image)
: http_request(uri__),
  image__(image)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image__.type();
    http_request::add_content("file", fname, image.bytearray());
}

void vision_batch::deserialise(std::string json_str)
{
    if (json_str.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json;
    try {
        json = json::parse(json_str);
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    for (auto obj_array : json) {
        for(const auto obj : services__) {
            if (!obj_array[obj.first].empty()) {
                // obj.second = vision_class / boost::variant
                obj.second.deserialise(obj_array[obj.first].dump());
            }
        }
    }
}

void vision_batch::end()
{
    http_request::close();
}

}
}
