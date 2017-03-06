#include "vision_detection.hpp"
namespace rapp 
{
namespace cloud 
{

//service names
const std::string face_detection::uri = "face_detection";
const std::string door_angle_detection::uri = "hazard_detection_door_check";
const std::string light_detection::uri= "light_detection";
const std::string human_detection::uri= "human_detection";
const std::string object_detection_learn_object::uri= "object_detection_learn_object";
const std::string object_detection_clear_models::uri= "object_detection_clear_models";
const std::string object_detection_load_models::uri= "object_detection_load_models";
const std::string object_detection_find_objects::uri= "object_detection_find_objects";

///Class face_detection
face_detection::face_detection(
                                const rapp::object::picture & image,
                                bool fast,
                                callback delegate
                              )
: http_request(make_http_uri(uri)),
  cloud_base(true),
  fast(fast),
  delegate(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"fast", fast}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

face_detection::face_detection(
                                bool fast,
                                callback delegate
                              )
: http_request(make_http_uri(uri)),
  cloud_base(false),
  fast(fast),
  delegate(delegate)
{}

std::string face_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"fast", fast}};
    return json_doc.dump(-1);
}

///Class door_angle_detection
door_angle_detection::door_angle_detection(
                                            const rapp::object::picture & image,
                                            callback delegate
                                          )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

door_angle_detection::door_angle_detection(callback delegate)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate(delegate)
{}

std::string door_angle_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

/// Class light_detection
light_detection::light_detection(
                                  const rapp::object::picture & image,
                                  callback delegate
                                )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

light_detection::light_detection(callback delegate)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate(delegate)
{
    nlohmann::json json_doc;
    http_request::add_content("light_detection", json_doc.dump(-1), true);
}

std::string light_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

/// Class human_detection
human_detection::human_detection(
                                  const rapp::object::picture & image,
                                  callback delegate
                                )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

human_detection::human_detection(callback delegate)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate(delegate)
{}

std::string human_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

/// Class object_detection_learn_object
object_detection_learn_object::object_detection_learn_object(
                                                              const rapp::object::picture & image,
                                                              const std::string name,
                                                              const std::string user,
                                                              callback delegate
                                                            )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  name(name),
  user(user),
  delegate(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"name", name},
                               {"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}
    
object_detection_learn_object::object_detection_learn_object(
                                                              const std::string name,
                                                              const std::string user,
                                                              callback delegate
                                                            )
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  name(name),
  user(user),
  delegate(delegate)
{}

std::string object_detection_learn_object::make_parameters() const
{
    nlohmann::json json_doc = {{"name", name},
                               {"user", user}};
    return json_doc.dump(-1);
}

/// Class object_detection_clear_models
object_detection_clear_models::object_detection_clear_models(
                                                              const std::string user,
                                                              callback delegate
                                                            )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate(delegate)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

///Class object_detection_load_models
object_detection_load_models::object_detection_load_models(
                                                            const std::string user,
                                                            const std::vector<std::string> names,
                                                            callback delegate
                                                          )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate(delegate)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user},
                     {"names", names}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

/// Class object_detection_find_objects
object_detection_find_objects::object_detection_find_objects(
                                                              const rapp::object::picture & image,
                                                              const std::string user,
                                                              const int limit,
                                                              callback delegate
                                                             )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  user(user),
  limit(limit),
  delegate(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"user", user},
                     {"limit", limit}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

object_detection_find_objects::object_detection_find_objects(
                                                              const std::string user,
                                                              const int limit,
                                                              callback delegate
                                                             )
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  user(user),
  limit(limit),
  delegate(delegate)
{}

std::string object_detection_find_objects::make_parameters() const
{
    nlohmann::json json_doc = {{"user", user},
                               {"limit", limit}};
    return json_doc.dump(-1);
}

}
}
