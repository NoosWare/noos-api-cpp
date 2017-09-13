#ifndef NOOS_OBJECT_FACE_RECOGNITION
#define NOOS_OBJECT_FACE_RECOGNITION
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include "face.hpp"
namespace noos {
/// @brief common object namespace
namespace object {
/**
 * @class face_recognition_obj
 * @brief describes a face coordinate,
 *        the label and the confidence of 
 *        the result
 * @version 0.8.0
 * @date 13.09.2017
 */
struct face_recognition_obj
{
    /// @brief rectangle which contains the face
    face face_rect;
    /// @brief confidence of the result
    double confidence;
    /// @brief label
    std::string label;

    /// @brief Constructor using `json for modern C++`
    face_recognition_obj(const json::const_iterator & face_it);
   
    /// @return json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const face_recognition_obj & rhs) const;

};
}
}
#endif
