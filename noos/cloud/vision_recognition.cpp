#include "vision_recognition.hpp"
namespace noos {
namespace cloud {

//service names
const std::string object_recognition::uri = "object_recognition";
const std::string qr_recognition::uri = "qr_recognition";
const std::string face_expression::uri = "face_expression";
const std::string face_recognition::uri = "face_recognition";

/// Class object_recognition
object_recognition::object_recognition(noos::object::picture image)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

object_recognition::object_recognition()
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}

/// CLass qr_recognition
qr_recognition::qr_recognition(noos::object::picture image)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

qr_recognition::qr_recognition()
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}}; 
    vision_base::json = json_doc.dump(-1);
}

face_expression::face_expression(noos::object::picture image)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

face_expression::face_expression()
: http_request(make_http_uri(uri)),
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}

face_recognition::face_recognition(noos::object::picture image)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

face_recognition::face_recognition()
: http_request(make_http_uri(uri)),
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}
}
}
