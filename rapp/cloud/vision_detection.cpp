#include "vision_detection.hpp"
namespace rapp 
{
namespace cloud 
{

const std::string face_detection::face_post__ = "POST /face_detection HTTP/1.1\r\n";   
const std::string door_angle_detection::door_post__ = "POST /hazard_detection_door_check HTTP/1.1\r\n";
const std::string light_detection::light_post__ = "POST /light_detection HTTP/1.1\r\n";
const std::string human_detection::human_post__ = "POST /human_detection HTTP/1.1\r\n";
const std::string object_detection_learn_object::learn_object_post__ = "POST /object_detection_learn_object HTTP/1.1\r\n";
const std::string object_detection_clear_models::clear_post__ = "POST /object_detection_clear_models HTTP/1.1\r\n";
const std::string object_detection_load_models::load_post__ = "POST /object_detection_load_models HTTP/1.1\r\n";
const std::string object_detection_find_objects::find_obj_post__ = "POST /object_detection_find_objects HTTP/1.1\r\n";

///Class face_detection
face_detection::face_detection(
                                const rapp::object::picture & image,
                                bool fast,
                                face_detect_callback callback
                              )
: http_request(face_post__),
  delegate_(callback) 
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    json json_doc = {{"fast", fast}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

face_detection::face_detection(
                                bool fast,
                                face_detect_callback callback
                              )
: http_request(face_post__),
  delegate_(callback)
{
    single_callable = false;
    json json_doc = {{"fast", fast}};
    http_request::add_content("face_detection", json_doc.dump(-1), true);
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

///Class door_angle_detection
door_angle_detection::door_angle_detection(
                                            const rapp::object::picture & image,
                                            door_callback callback
                                          )
: http_request(door_post__), 
  delegate_(callback)
{

    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

door_angle_detection::door_angle_detection(door_callback callback)
: http_request(door_post__), 
  delegate_(callback)
{
    single_callable = false;
    json json_doc;
    http_request::add_content("door_angle_detection", json_doc.dump(-1), true);
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

/// Class light_detection
light_detection::light_detection(
                                  const rapp::object::picture & image,
                                  light_callback callback
                                )
: http_request(light_post__), 
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

light_detection::light_detection(light_callback callback)
: http_request(light_post__), 
  delegate_(callback)
{
    single_callable = false;
    json json_doc;
    http_request::add_content("light_detection", json_doc.dump(-1), true);
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

/// Class human_detection
human_detection::human_detection(
                                  const rapp::object::picture & image,
                                  human_callback callback
                                )
: http_request(human_post__), 
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    http_request::add_content("file", fname, image.bytearray());
    http_request::close();
}

human_detection::human_detection(human_callback callback)
: http_request(human_post__), 
  delegate_(callback)
{
    single_callable = false;
    json json_doc;
    http_request::add_content("human_detection", json_doc.dump(-1), true);
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
/// Class object_detection_learn_object
object_detection_learn_object::object_detection_learn_object(
                                                              const rapp::object::picture & image,
                                                              const std::string name,
                                                              const std::string user,
                                                              learn_callback callback
                                                            )
: http_request(learn_object_post__), 
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    json json_doc = {{"name", name},
                     {"user", user}};
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
  delegate_(callback)
{
    single_callable = false;
    json json_doc = {{"name", name},
                     {"user", user}};
    http_request::add_content("object_detection_learn_object", json_doc.dump(-1), true);
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

/// Class object_detection_clear_models
object_detection_clear_models::object_detection_clear_models(
                                                              const std::string user,
                                                              clear_callback callback
                                                            )
: http_request(clear_post__), 
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    json json_doc = {{"user", user}};
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

///Class object_detection_load_models
object_detection_load_models::object_detection_load_models(
                                                            const std::string user,
                                                            const std::vector<std::string> names,
                                                            load_callback callback
                                                          )
: http_request(load_post__), 
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    json json_doc = {{"user", user},
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

/// Class object_detection_find_objects
object_detection_find_objects::object_detection_find_objects(
                                                              const rapp::object::picture & image,
                                                              const std::string user,
                                                              const int limit,
                                                              find_callback callback
                                                             )
: http_request(find_obj_post__), 
  delegate_(callback)
{
    single_callable = true;
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary() + "." + image.type();
    json json_doc = {{"user", user},
                     {"limit", limit}};
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
  delegate_(callback)
{
    single_callable = false;
    json json_doc = {{"user", user},
                     {"limit", limit}};
    http_request::add_content("object_detection_find_object", json_doc.dump(-1), true);
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

}
}
