#include "deserialize.hpp"
namespace noos {
namespace cloud {
/// Forward - Delcare all classes for which we create template specializations
struct face_detection;
struct light_detection;
struct human_detection;
struct object_detection_learn_object;
struct object_detection_clear_models;
struct object_detection_load_models;
struct object_detection_find_objects;
struct object_recognition;
struct qr_recognition;

// face_detection and faces
template <>
inline std::vector<noos::object::face> 
    deserialize<face_detection,std::vector<noos::object::face>>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<noos::object::face> faces;
    nlohmann::json json_f;

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_faces = json_f.find("faces");
            for (auto it = it_faces->begin(); it != it_faces->end(); it++ ) {
                faces.push_back(noos::object::face(it));
            }
        }
    }
    return faces;
}

// light detection
template <>
inline int 
    deserialize<light_detection,int>::operator()(std::string json)
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
// human detection
template <>
inline std::vector<noos::object::human> 
    deserialize<human_detection,std::vector<noos::object::human>>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<noos::object::human> humans;
    nlohmann::json json_f; 

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_human = json_f.find("humans");
            for (auto it = it_human->begin(); it != it_human->end(); it++ ) {
                humans.push_back(noos::object::human(it));
            }
        }
    }
    return humans;
}

// ORB learn models
template <>
inline int 
    deserialize<orb_learn_object,int>::operator()(std::string json) 
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

// ORB clear models
template <>
inline int 
    deserialize<orb_clear_models,int>::operator()(std::string json) 
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

// ORB load models
template <>
inline int 
    deserialize<orb_load_models,int>::operator()(std::string json) 
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

// ORB find objects
template <>
inline noos::object::orb_object 
    deserialize<object_detection_find_objects,noos::object::orb_object>::operator()(std::string json) 
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    std::vector<noos::object::point> points;
    nlohmann::json json_f;

    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_center = json_f.find("found_centers");
            for (auto it = it_center->begin(); it != it_center->end(); it++) {
                points.push_back(noos::object::point(it));
            }
            return noos::object::orb_object {
                                              json_f["found_names"],
                                              points, 
                                              json_f["found_scores"],
                                              json_f["result"]
                                            };
        }
    }
    return noos::object::orb_object{};
}

// object recognition (Caffe2)
template <>
inline std::string 
    deserialize<object_recognition,std::string>::operator()(std::string json) 
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["object_class"]);
        }
    }
    return "";
}

// QR recongition
template<>
inline std::vector<noos::object::qr_code> 
    deserialize<qr_recognition,std::vector<noos::object::qr_code>>::operator()(std::string json)
{
    std::vector<noos::object::qr_code> qr_codes;
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            unsigned int i = 0;
            for (auto & obj : json_f["qr_centers"]) {
                qr_codes.push_back(noos::object::qr_code(obj["x"], obj["y"], json_f["qr_messages"].at(i)));
                i++;
            }
            return qr_codes;
        }
    }
    return qr_codes;
}

// available services
template<>
inline std::vector<std::pair<std::string,std::string>>
    deserialize<available_services,std::vector<std::pair<std::string,std::string>>>::operator()(std::string json)
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    std::vector<service> services;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            for (auto it_s : json_f["services"]) {
                services.push_back(std::make_pair(misc::get_json_value<std::string>("name", it_s), 
                                                  misc::get_json_value<std::string>("url", it_s)));
            }
        }
    }
    return services;
}

}
}

