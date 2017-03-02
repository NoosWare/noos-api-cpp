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
                                face_detect_callback callback
                              )
: http_request(make_http_uri(uri)),
  cloud_base(true),
  fast_(fast),
  delegate_(callback)
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
                                face_detect_callback callback
                              )
: http_request(make_http_uri(uri)),
  cloud_base(false),
  fast_(fast),
  delegate_(callback)
{}

std::string face_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"fast", fast_}};
    return json_doc.dump(-1);
}

void face_detection::deserialise(std::string json) const
{   
    delegate_(rapp::cloud::deserialize<face_detection,std::vector<rapp::object::face>>()(json));
}

///Class door_angle_detection
door_angle_detection::door_angle_detection(
                                            const rapp::object::picture & image,
                                            door_callback callback
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

door_angle_detection::door_angle_detection(door_callback callback)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate_(callback)
{}

std::string door_angle_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

void door_angle_detection::deserialise(std::string json) const
{
   delegate_(rapp::cloud::deserialize<door_angle_detection, double>()(json));
}

/// Class light_detection
light_detection::light_detection(
                                  const rapp::object::picture & image,
                                  light_callback callback
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

light_detection::light_detection(light_callback callback)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate_(callback)
{
    nlohmann::json json_doc;
    http_request::add_content("light_detection", json_doc.dump(-1), true);
}

std::string light_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

void light_detection::deserialise(std::string json) const
{
   delegate_(rapp::cloud::deserialize<light_detection, int>()(json));
}

/// Class human_detection
human_detection::human_detection(
                                  const rapp::object::picture & image,
                                  human_callback callback
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

human_detection::human_detection(human_callback callback)
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  delegate_(callback)
{}

std::string human_detection::make_parameters() const
{
    nlohmann::json json_doc = {{"no_param", ""}};
    return json_doc.dump(-1);
}

void human_detection::deserialise(std::string json) const
{
    delegate_(rapp::cloud::deserialize<human_detection, std::vector<rapp::object::human>>()(json));
}

/// Class object_detection_learn_object
object_detection_learn_object::object_detection_learn_object(
                                                              const rapp::object::picture & image,
                                                              const std::string name,
                                                              const std::string user,
                                                              learn_callback callback
                                                            )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  name__(name),
  user__(user),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"name", name__},
                               {"user", user__}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}
    
object_detection_learn_object::object_detection_learn_object(
                                                              const std::string name,
                                                              const std::string user,
                                                              learn_callback callback
                                                            )
: http_request(make_http_uri(uri)), 
  cloud_base(false),
  name__(name),
  user__(user),
  delegate_(callback)
{}

std::string object_detection_learn_object::make_parameters() const
{
    nlohmann::json json_doc = {{"name", name__},
                               {"user", user__}};
    return json_doc.dump(-1);
}

void object_detection_learn_object::deserialise(std::string json) const 
{   
    delegate_(rapp::cloud::deserialize<object_detection_learn_object, int>()(json));
}

/// Class object_detection_clear_models
object_detection_clear_models::object_detection_clear_models(
                                                              const std::string user,
                                                              clear_callback callback
                                                            )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void object_detection_clear_models::deserialise(std::string json) const 
{
    delegate_(rapp::cloud::deserialize<object_detection_clear_models, int>()(json));
}

///Class object_detection_load_models
object_detection_load_models::object_detection_load_models(
                                                            const std::string user,
                                                            const std::vector<std::string> names,
                                                            load_callback callback
                                                          )
: http_request(make_http_uri(uri)), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user},
                     {"names", names}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void object_detection_load_models::deserialise(std::string json) const 
{
   delegate_(rapp::cloud::deserialize<object_detection_load_models, int>()(json));
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
  user__(user),
  limit__(limit),
  delegate_(delegate)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    nlohmann::json json_doc = {{"user", user__},
                     {"limit", limit__}};
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
  user__(user),
  limit__(limit),
  delegate_(delegate)
{}

std::string object_detection_find_objects::make_parameters() const
{
    nlohmann::json json_doc = {{"user", user__},
                               {"limit", limit__}};
    return json_doc.dump(-1);
}

void object_detection_find_objects::deserialise(std::string json) const {

   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::point> points;
    nlohmann::json json_f;

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_center = json_f.find("found_centers");
            for (auto it = it_center->begin(); it != it_center->end(); it++) {
                points.push_back(rapp::object::point(it));
            }
            /**
             * TODO: replace with `rapp::object::orb_object`
            delegate_(json_f["found_names"],
                      points, 
                      json_f["found_scores"],
                      json_f["result"]);
              */
        }
    }
}

}
}
