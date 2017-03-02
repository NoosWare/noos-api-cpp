#ifndef DESERIALIZE_HPP
#define DESERIALIZE_HPP
namespace rapp
{
namespace cloud
{
/// Generic template
template <class service_type, class return_type>
struct deserialize
{
    return_type operator()(std::string json);
};

class face_detection;
class door_angle_detection;
class light_detection;
class human_detection;
class object_detection_learn_object;
class object_detection_clear_models;
class object_detection_load_models;
class object_detection_find_objects;


/// specialization for face_detection and faces
template <>
inline std::vector<rapp::object::face> deserialize<face_detection,std::vector<rapp::object::face>>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::face> faces;
    nlohmann::json json_f;

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_faces = json_f.find("faces");
            for (auto it = it_faces->begin(); it != it_faces->end(); it++ ) {
                faces.push_back(rapp::object::face(it));
            }
        }
    }
    return faces;
}

template <>
inline double deserialize<door_angle_detection,double>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return json_f["door_angle"];
        }
    }
    return -1; // ?? makes sense??
}

template <>
inline int deserialize<light_detection,int>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["light_level"]);
        }
    }
    return -1;
}

template <>
inline std::vector<rapp::object::human> 
deserialize<human_detection,std::vector<rapp::object::human>>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<rapp::object::human> humans;
    nlohmann::json json_f; 

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_human = json_f.find("humans");
            for (auto it = it_human->begin(); it != it_human->end(); it++ ) {
                humans.push_back(rapp::object::human(it));
            }
        }
    }
    return humans;
}

template <>
inline int deserialize<object_detection_learn_object,int>::operator()(std::string json) 
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["result"]);
        }
    }
    return -1; 
}

template <>
inline int deserialize<object_detection_clear_models,int>::operator()(std::string json) 
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["result"]);
        }
    }
    return -1; 
}

template <>
inline int deserialize<object_detection_load_models,int>::operator()(std::string json) 
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["result"]);
        }
    }
    return -1; 
}

//template <>
//int deserialize<object_detection_load_models, int>::operator()(std::string json) 
//{
//    if (json.empty()) {
//        throw std::runtime_error("empty json reply");
//    }
//    std::vector<rapp::object::point> points;
//    nlohmann::json json_f;
//
//    if (misc::check_json(json_f, json)) {
//        if (misc::check_error(json_f)) {
//            auto it_center = json_f.find("found_centers");
//            for (auto it = it_center->begin(); it != it_center->end(); it++) {
//                points.push_back(rapp::object::point(it));
//            }
//            //delegate_(json_f["found_names"],
//            //          points, 
//            //          json_f["found_scores"],
//            //          json_f["result"]);
//        }
//    }
//    return -1;
//}

// TODO: you repeat this for each cloud class, simply copy-pasting their code in each specialization
// so when you store a lambda/std::function you will store:
//  (const std::string json){ return deserialize<face_detection, face>(json); }
// for each service value in they key map
}
}
#endif
