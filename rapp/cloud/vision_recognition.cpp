#include "vision_recognition.hpp"
namespace rapp {
namespace cloud {

//service names
const std::string object_recognition::uri = "object_recognition_caffe";
const std::string qr_recognition::uri = "qr_detection";

/// Class object_recognition
object_recognition::object_recognition(
                                        const rapp::object::picture & image,
                                        object_recognition_callback callback
                                      )
: http_request(make_http_uri(uri)), 
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
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate_(callback)
{}

std::string object_recognition::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

void object_recognition::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            delegate_(json_f["object_class"]);
        }
    }    
}

/// CLass qr_recognition
qr_recognition::qr_recognition(
                                const rapp::object::picture & image,
                                qr_callback callback
                              )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

qr_recognition::qr_recognition(qr_callback callback)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate_(callback)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    http_request::add_content("qr_detection", json_doc.dump(-1), true);

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
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            unsigned int i = 0;
            for (auto & obj : json_f["qr_centers"]) {
                qr_codes.push_back(rapp::object::qr_code(obj["x"], obj["y"], json_f["qr_messages"].at(i)));
                i++;
            }
            delegate_(qr_codes);
        }
    }
}

}
}
