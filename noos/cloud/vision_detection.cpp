#include "vision_detection.hpp"
namespace noos {
namespace cloud {

//service names
const std::string face_detection::uri   = "face_detection";
const std::string light_detection::uri  = "light_detection";
const std::string human_detection::uri  = "human_detection";
const std::string gender_detection::uri = "gender_detection";
const std::string age_detection::uri    = "age_detection";
const std::string orb_learn_object::uri = "orb_learn_object";
const std::string orb_clear_models::uri = "orb_clear_models";
const std::string orb_load_models::uri  = "orb_load_models";
const std::string orb_find_objects::uri = "orb_find_objects";

face_detection::face_detection(const noos::object::picture & image)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"fast", true}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

face_detection::face_detection()
: http_request(make_http_uri(uri)),
  cloud_base(false)
{
    nlohmann::json json_doc = {{"fast", true}};
    vision_base::json = json_doc.dump(-1);
}

light_detection::light_detection(const noos::object::picture & image)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

light_detection::light_detection()
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}

human_detection::human_detection(const noos::object::picture & image)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

human_detection::human_detection()
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}

gender_detection::gender_detection(const noos::object::picture & image)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

gender_detection::gender_detection()
: http_request(make_http_uri(uri)),
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}

age_detection::age_detection(const noos::object::picture & image)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

age_detection::age_detection()
: http_request(make_http_uri(uri)),
  cloud_base(false)
{
    nlohmann::json json_doc = {{"no_param", ""}};
    vision_base::json = json_doc.dump(-1);
}

orb_learn_object::orb_learn_object(const noos::object::picture & image,
                                   const std::string name)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"name", name}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}
    
orb_learn_object::orb_learn_object(const std::string name)
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"name", name}};
    vision_base::json = json_doc.dump(-1);
}

orb_clear_models::orb_clear_models(const std::string user)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

///Class orb_load_models
orb_load_models::orb_load_models(const std::vector<std::string> names)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"names", names}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

/// Class orb_find_objects
orb_find_objects::orb_find_objects(const noos::object::picture & image,
                                   const int limit)
: http_request(make_http_uri(uri)), 
  cloud_base(true)
{
    http_request::make_multipart_form();
    std::string fname = noos::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"limit", limit}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

orb_find_objects::orb_find_objects(const int limit)
: http_request(make_http_uri(uri)), 
  cloud_base(false)
{
    nlohmann::json json_doc = {{"limit", limit}};
    vision_base::json = json_doc.dump(-1);
}

}
}
