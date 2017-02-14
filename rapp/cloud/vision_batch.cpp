#include "vision_batch.hpp"

namespace rapp
{
namespace cloud
{

const std::string vision_batch::batch_post__ = "POST /vision_batch HTTP/1.1\r\n";

vision_batch::vision_batch(const rapp::object::picture & image)
: http_request(batch_post__),
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
    for(const auto obj : services__) {
        obj.second->deserialise(json[obj.first]);
    }
}

void vision_batch::end()
{
    http_request::close();
}

}
}
