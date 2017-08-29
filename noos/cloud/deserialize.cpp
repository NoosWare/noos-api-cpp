#include "deserialize.hpp"

namespace noos {
namespace cloud {
/// Forward - Delcare all classes for which we create template specializations
struct available_services;
struct face_detection;
struct light_detection;
struct human_detection;
struct orb_learn_object;
struct orb_clear_models;
struct orb_load_models;
struct orb_find_objects;
struct object_recognition;
struct qr_recognition;
struct icp_slam;

// face_detection and faces
template <>
std::vector<noos::object::face> 
    deserialize<face_detection,
                std::vector<noos::object::face>
               >::operator()(std::string json)
{
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
int deserialize<light_detection,
                int
                >::operator()(std::string json)
{
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
std::vector<noos::object::human> 
    deserialize<human_detection,
                std::vector<noos::object::human>
                >::operator()(std::string json)
{
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
int deserialize<orb_learn_object,
                int
                >::operator()(std::string json) 
{
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
int deserialize<orb_clear_models,
                int
                >::operator()(std::string json) 
{
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
int deserialize<orb_load_models,
                int
                >::operator()(std::string json) 
{
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
noos::object::orb_object 
    deserialize<orb_find_objects,
                noos::object::orb_object
               >::operator()(std::string json) 
{
    std::vector<noos::object::point<double>> points;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_center = json_f.find("found_centers");
            for (auto it = it_center->begin(); it != it_center->end(); it++) {
                points.push_back(noos::object::point<double>(it));
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
std::string 
    deserialize<object_recognition,
                std::string
                >::operator()(std::string json) 
{
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
std::vector<noos::object::qr_code> 
    deserialize<qr_recognition,
                std::vector<noos::object::qr_code>
                >::operator()(std::string json)
{
    std::vector<noos::object::qr_code> qr_codes;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_qrs = json_f.find("qrs");
            for (auto it = it_qrs->begin(); it != it_qrs->end(); it++ ) {
                qr_codes.push_back(noos::object::qr_code(it));
            }
        }
    }
    return qr_codes;
}

// available services
template<>
std::vector<std::string>
    deserialize<available_services,
                std::vector<std::string>
                >::operator()(std::string json)
{
    nlohmann::json json_f;
    std::vector<std::string> services;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            for (auto it_s : json_f["services"]) {
                services.push_back(misc::get_json_value<std::string>("name", it_s));
            }
        }
    }
    return services;
}

template<>
noos::object::pose<float> deserialize<icp_slam,
                                      noos::object::pose<float>
                                     >::operator()(std::string json)
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
           noos::object::pose<float>pose3d(json_f.find("pose")); 
           return pose3d;
        }
    }
    noos::object::pose<float> empty_pose;
    return empty_pose;
}

}
}

