#ifndef DESERIALIZE_HPP
#define DESERIALIZE_HPP
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <rapp/objects.hpp>

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

/// Forward - Delcare all classes for which we create template specializations
struct face_detection;
struct door_angle_detection;
struct light_detection;
struct human_detection;
struct object_detection_learn_object;
struct object_detection_clear_models;
struct object_detection_load_models;
struct object_detection_find_objects;
struct object_recognition;
struct qr_recognition;

/// Vision classes
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

/// specialization for door angle detection
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

/// specialization for light detection
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
/// specialization for human detection
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

/// specialization for learn object detection
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

/// specialization for clear models
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

/// specialization for load models
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

/// specialization for find objects
template <>
inline rapp::object::orb_object deserialize<object_detection_find_objects,rapp::object::orb_object>::operator()(std::string json) 
{
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
            return rapp::object::orb_object {
                                              json_f["found_names"],
                                              points, 
                                              json_f["found_scores"],
                                              json_f["result"]
                                            };
        }
    }
    return rapp::object::orb_object{};
}

template <>
inline std::string deserialize<object_recognition,std::string>::operator()(std::string json) 
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

template<>
inline std::vector<rapp::object::qr_code> deserialize<qr_recognition, std::vector<rapp::object::qr_code>>::operator()(std::string json)
{
    std::vector<rapp::object::qr_code> qr_codes;
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if (misc::check_json(json_f, json)) {
        if (misc::check_error(json_f)) {
            unsigned int i = 0;
            for (auto & obj : json_f["qr_centers"]) {
                qr_codes.push_back(rapp::object::qr_code(obj["x"], obj["y"], json_f["qr_messages"].at(i)));
                i++;
            }
            return qr_codes;
        }
    }
    return qr_codes;
}

}
}
#endif
