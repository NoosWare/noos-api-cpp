#include "deserialize.hpp"

namespace noos {
namespace cloud {
/// Forward - Delcare all classes for which we create template specializations
struct available_services;
struct face_detection;
struct light_detection;
struct human_detection;
struct orb_learn_object;
struct orb_clear_model;
struct orb_find_objects;
struct object_recognition;
struct qr_recognition;
struct age_detection;
struct gender_detection;
struct face_expression;
struct icp_slam;
struct rbpf_slam;
struct delete_map;
struct upload_map;
struct upload_slam_config_file;
struct get_map;
struct face_recognition;
struct path_planning;

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

// object recognition (Caffe2)
template <>
std::vector<std::pair<std::string,float>>
    deserialize<object_recognition,
                std::vector<std::pair<std::string,float>>
                >::operator()(std::string json) 
{
    std::vector<std::pair<std::string,float>> result;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto results = json_f.find("result");
            for (auto it = results->begin(); it != results->end(); it++) {
                result.push_back(
                        std::make_pair(it->find("label")->get<std::string>(),
                                       it->find("probability")->get<float>()));
            }
        }
    }
    return result;
}

// gender_detection (Caffe2)
template <>
std::vector<std::pair<std::string,float>>
    deserialize<gender_detection,
                std::vector<std::pair<std::string,float>>
                >::operator()(std::string json)
{
    std::vector<std::pair<std::string,float>> result;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto results = json_f.find("result");
            for (auto it = results->begin(); it != results->end(); it++) {
                result.push_back(
                        std::make_pair(it->find("label")->get<std::string>(),
                                       it->find("probability")->get<float>()));            
            }
        }
    }
    return result;
}

// age_detection (Caffe2)
template<>
std::vector<std::pair<std::string,float>>
    deserialize<age_detection,
                std::vector<std::pair<std::string,float>>
                >::operator()(std::string json)
{
    std::vector<std::pair<std::string,float>> result;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto results = json_f.find("result");
            for (auto it = results->begin(); it != results->end(); it++) {
                result.push_back(
                        std::make_pair(it->find("label")->get<std::string>(),
                                       it->find("probability")->get<float>()));            
            }
        }
    }
    return result;
}

// face_expression (Caffe2)
template<>
std::vector<std::pair<std::string,float>>
    deserialize<face_expression,
                std::vector<std::pair<std::string,float>>
                >::operator()(std::string json)
{
    std::vector<std::pair<std::string,float>> result;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto results = json_f.find("result");
            for (auto it = results->begin(); it != results->end(); it++) {
                result.push_back(
                        std::make_pair(it->find("label")->get<std::string>(),
                                       it->find("probability")->get<float>()));            
            }
        }
    }
    return result;
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

// ORB learn models
template <>
bool deserialize<orb_learn_object,
                bool 
                >::operator()(std::string json) 
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["result"]);
        }
    }
    return false; 
}

// ORB clear models
template <>
bool deserialize<orb_clear_model,
                bool
                >::operator()(std::string json) 
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            return(json_f["result"]);
        }
    }
    return false; 
}

// ORB find objects
template <>
std::vector<noos::object::point2d<float>> 
    deserialize<orb_find_objects,
                std::vector<noos::object::point2d<float>>
               >::operator()(std::string json) 
{
    std::vector<noos::object::point2d<float>> points;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_center = json_f.find("keypoints");
            for (auto it = it_center->begin(); it != it_center->end(); it++) {
                points.push_back(noos::object::point2d<float>(it));
            }
        }
    }
    return points;
}

// icp slam
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

// rbpf slam
template<>
noos::object::pose<float> deserialize<rbpf_slam,
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

// delete map
template <>
bool deserialize<delete_map,
                 bool>:: operator()(std::string json)
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
           return json_f["success"];
        }
    }
    return false;
}

// upload map
template <>
bool deserialize<upload_map,
                 bool>:: operator()(std::string json)
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
           return json_f["success"];
        }
    }
    return false;
}

// upload config file
template <>
bool deserialize<upload_slam_config_file,
                 bool>:: operator()(std::string json)
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
           return json_f["success"];
        }
    }
    return false;
}

// get map image
template <>
bool deserialize<get_map,
                 bool>:: operator()(std::string json)
{
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f) &&
            misc::save_dec_image(json_f["image"], json_f["map_name"])) {
           return json_f["success"];
        }
    }
    return false;
}

// face recognition
template <>
std::vector<noos::object::person> 
    deserialize<face_recognition,
                std::vector<noos::object::person>
               >::operator()(std::string json)
{
    std::vector<noos::object::person> faces;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_faces = json_f.find("faces");
            for (auto it = it_faces->begin(); it != it_faces->end(); it++ ) {
                faces.push_back(noos::object::person(it));
            }
        }
    }
    return faces;
}

// path_planning
template <>
std::deque<noos::object::point2d<float>> 
    deserialize<path_planning,
                std::deque<noos::object::point2d<float>>
               >::operator()(std::string json)
{
    std::deque<noos::object::point2d<float>> points;
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            auto it_points = json_f.find("points");
            for (auto it = it_points->begin(); it != it_points->end(); it++ ) {
                points.push_back(noos::object::point2d<float>(it));
            }
        }
    }
    return points;
}

}
}
