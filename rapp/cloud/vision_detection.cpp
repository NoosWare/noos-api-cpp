#include "vision_detection.hpp"
namespace rapp 
{
namespace cloud 
{

//service names
const std::string face_detection::face_service__ = "face_detection";
const std::string door_angle_detection::door_service__ = "hazard_detection_door_check";
const std::string light_detection::light_service__ = "light_detection";
const std::string human_detection::human_service__ = "human_detection";
const std::string object_detection_learn_object::learn_object_service__ = "object_detection_learn_object";
const std::string object_detection_clear_models::clear_service__ = "object_detection_clear_models";
const std::string object_detection_load_models::load_service__ = "object_detection_load_models";
const std::string object_detection_find_objects::find_obj_service__ = "object_detection_find_objects";
//POST
const std::string face_detection::face_post__ = "POST /" + face_service__ + " HTTP/1.1\r\n";   
const std::string door_angle_detection::door_post__ = "POST /" + door_service__ + " HTTP/1.1\r\n";
const std::string light_detection::light_post__ = "POST /" + light_service__ + " HTTP/1.1\r\n";
const std::string human_detection::human_post__ = "POST /" + human_service__ + " HTTP/1.1\r\n";
const std::string object_detection_learn_object::learn_object_post__ = "POST /" + learn_object_service__ + " HTTP/1.1\r\n";
const std::string object_detection_clear_models::clear_post__ = "POST /" + clear_service__ + " HTTP/1.1\r\n";
const std::string object_detection_load_models::load_post__ = "POST /" + load_service__ + " HTTP/1.1\r\n";
const std::string object_detection_find_objects::find_obj_post__ = "POST /" + find_obj_service__ + " HTTP/1.1\r\n";

///Class face_detection
face_detection::face_detection(
                                const rapp::object::picture & image,
                                bool fast,
                                face_detect_callback callback
                              )
: http_request(face_post__),
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
: http_request(face_post__),
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
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::face> faces;
    nlohmann::json json_f;

    if(misc::check_json(json_f, json)) {
        auto it_faces = json_f.find("faces");
        for (auto it = it_faces->begin(); it != it_faces->end(); it++ ) {
            faces.push_back(rapp::object::face(it));
        }
        delegate_(faces);
    }
}

void face_detection::deserialise(nlohmann::json json) const
{   
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::face> faces;
    if(misc::check_error(json)) {
        auto it_faces = json.find("faces");
        for (auto it = it_faces->begin(); it != it_faces->end(); it++ ) {
            faces.push_back(rapp::object::face(it));
        }
        delegate_(faces);
    }
}

std::string face_detection::get_name() const
{
    return face_service__;
}

///Class door_angle_detection
door_angle_detection::door_angle_detection(
                                            const rapp::object::picture & image,
                                            door_callback callback
                                          )
: http_request(door_post__), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

door_angle_detection::door_angle_detection(door_callback callback)
: http_request(door_post__), 
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
   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["door_angle"]);
    }
}

void door_angle_detection::deserialise(nlohmann::json json) const
{
   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    if(misc::check_error(json)) {
        delegate_(json["door_angle"]);
    }
}

std::string door_angle_detection::get_name() const
{
    return door_service__;
}

/// Class light_detection
light_detection::light_detection(
                                  const rapp::object::picture & image,
                                  light_callback callback
                                )
: http_request(light_post__), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

light_detection::light_detection(light_callback callback)
: http_request(light_post__), 
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
   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["light_level"]);
    }
}

void light_detection::deserialise(nlohmann::json json) const
{
   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_error(json)) {
        delegate_(json["light_level"]);
    }
}

std::string light_detection::get_name() const
{
    return light_service__;
}

/// Class human_detection
human_detection::human_detection(
                                  const rapp::object::picture & image,
                                  human_callback callback
                                )
: http_request(human_post__), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

human_detection::human_detection(human_callback callback)
: http_request(human_post__), 
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
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::human> humans;
    nlohmann::json json_f; 

    if(misc::check_json(json_f, json)) {
        auto it_human = json_f.find("humans");
        for (auto it = it_human->begin(); it != it_human->end(); it++ ) {
            humans.push_back(rapp::object::human(it));
        }
        delegate_(humans);
    }
}

void human_detection::deserialise(nlohmann::json json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::human> humans;

    if(misc::check_error(json)) {
        auto it_human = json.find("humans");
        for (auto it = it_human->begin(); it != it_human->end(); it++ ) {
            humans.push_back(rapp::object::human(it));
        }
        delegate_(humans);
    }
}

std::string human_detection::get_name() const
{
    return human_service__;
}

/// Class object_detection_learn_object
object_detection_learn_object::object_detection_learn_object(
                                                              const rapp::object::picture & image,
                                                              const std::string name,
                                                              const std::string user,
                                                              learn_callback callback
                                                            )
: http_request(learn_object_post__), 
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
: http_request(learn_object_post__), 
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

void object_detection_learn_object::deserialise(std::string json) const {

   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["result"]);
    }

}

void object_detection_learn_object::deserialise(nlohmann::json json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }

    if(misc::check_error(json)) {
        delegate_(json["result"]);
    }
}

std::string object_detection_learn_object::get_name() const
{
    return learn_object_service__;
}

/// Class object_detection_clear_models
object_detection_clear_models::object_detection_clear_models(
                                                              const std::string user,
                                                              clear_callback callback
                                                            )
: http_request(clear_post__), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}
    
void object_detection_clear_models::deserialise(std::string json) const {

   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;

    if(misc::check_json(json_f, json)) {
        delegate_(json_f["result"]);
    }

}

std::string object_detection_clear_models::get_name() const
{
    return clear_service__;
}

///Class object_detection_load_models
object_detection_load_models::object_detection_load_models(
                                                            const std::string user,
                                                            const std::vector<std::string> names,
                                                            load_callback callback
                                                          )
: http_request(load_post__), 
  cloud_base(true),
  delegate_(callback)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"user", user},
                     {"names", names}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void object_detection_load_models::deserialise(std::string json) const {

   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        delegate_(json_f["result"]);
    }

}

std::string object_detection_load_models::get_name() const
{
    return load_service__;
}

/// Class object_detection_find_objects
object_detection_find_objects::object_detection_find_objects(
                                                              const rapp::object::picture & image,
                                                              const std::string user,
                                                              const int limit,
                                                              find_callback callback
                                                             )
: http_request(find_obj_post__), 
  cloud_base(true),
  user__(user),
  limit__(limit),
  delegate_(callback)
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
                                                              find_callback callback
                                                             )
: http_request(find_obj_post__), 
  cloud_base(false),
  user__(user),
  limit__(limit),
  delegate_(callback)
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

    if(misc::check_json(json_f, json)) {
        auto it_center = json_f.find("found_centers");
        for (auto it = it_center->begin(); it != it_center->end(); it++) {
            points.push_back(rapp::object::point(it));
        }
        delegate_(json_f["found_names"],
                  points, 
                  json_f["found_scores"],
                  json_f["result"]);
    }
}

void object_detection_find_objects::deserialise(nlohmann::json json) const {

   if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::point> points;

    if(misc::check_error(json)) {
        auto it_center = json.find("found_centers");
        for (auto it = it_center->begin(); it != it_center->end(); it++) {
            points.push_back(rapp::object::point(it));
        }
        delegate_(json["found_names"],
                  points, 
                  json["found_scores"],
                  json["result"]);
    }
}

std::string object_detection_find_objects::get_name() const
{
    return find_obj_service__;
}

}
}
