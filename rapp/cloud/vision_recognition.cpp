#include "vision_recognition.hpp"
namespace rapp {
namespace cloud {

//service names
const std::string object_recognition::uri = "object_recognition_caffe";
const std::string qr_recognition::uri = "qr_detection";

/// Class object_recognition
object_recognition::object_recognition(const rapp::object::picture & image)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

object_recognition::object_recognition()
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    cloud_base::json = json_doc.dump(-1);
}

/// CLass qr_recognition
qr_recognition::qr_recognition(const rapp::object::picture & image)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

qr_recognition::qr_recognition()
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}}; 
    cloud_base::json = json_doc.dump(-1);
}

}
}
