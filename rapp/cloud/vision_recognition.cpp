#include "vision_recognition.hpp"
namespace rapp {
namespace cloud {

const std::string object_recognition::obj_recogn_post__ = "POST /object_recognition_caffe HTTP/1.1\r\n";
const std::string qr_recognition::qr_post__ = "POST /qr_detection HTTP/1.1\r\n";

/// Class object_recognition
object_recognition::object_recognition(
                                        const rapp::object::picture & image,
                                        object_recognition_callback callback
                                      )
: http_request(obj_recogn_post__), 
  cloud_base(true),
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

object_recognition::object_recognition(object_recognition_callback callback)
: http_request(obj_recogn_post__), 
  cloud_base(false),
  delegate_(callback)
{}

std::string object_recognition::make_parameters() const
{
    nlohmann::json json_doc;
    return json_doc.dump(-1);
}

void object_recognition::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["object_class"]);
    }    
}

void object_recognition::deserialise(nlohmann::json json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    if(misc::check_error(json)) {
        delegate_(json["object_class"]);
    }    
}

/// CLass qr_recognition
qr_recognition::qr_recognition(
                                const rapp::object::picture & image,
                                qr_callback callback
                              )
: http_request(qr_post__), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

qr_recognition::qr_recognition(qr_callback callback)
: http_request(qr_post__), 
  cloud_base(false),
  delegate_(callback)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    http_request::add_content("qr_recognition", json_doc.dump(-1), true);

}

std::string qr_recognition::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}}; 
    return json_doc.dump(-1);
}

void qr_recognition::deserialise(std::string json) const
{
    std::vector<rapp::object::qr_code> qr_codes;
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        unsigned int i = 0;
        for (auto & obj : json_f["qr_centers"]) {
            qr_codes.push_back(rapp::object::qr_code(obj["x"], obj["y"], json_f["qr_messages"].at(i)));
            i++;
        }
        delegate_(qr_codes);
    }
}

void qr_recognition::deserialise(nlohmann::json json) const
{
    std::vector<rapp::object::qr_code> qr_codes;
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    if(misc::check_error(json)) {
        unsigned int i = 0;
        for (auto & obj : json["qr_centers"]) {
            qr_codes.push_back(rapp::object::qr_code(obj["x"], obj["y"], json["qr_messages"].at(i)));
            i++;
        }
        delegate_(qr_codes);
    }
}

}
}
