#ifndef NOOS_OBJECT_FACE_RECOGNITION
#define NOOS_OBJECT_FACE_RECOGNITION
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include "face.hpp"
namespace noos {
/// @brief Common object namespace
namespace object {
/**
 * @struct person
 * @brief Describes a face coordinate,
 *        the label and the confidence of 
 *        the result
 * @version 0.8.0
 * @date 13.09.2017
 */
struct person
{
    /// @brief Rectangle which contains the face
    face face_rect;
    /// @brief Confidence of the result
    float confidence;
    /// @brief Name
    std::string name;
    /// @brief Label number
    int label;

    /// @brief Constructor using `json for modern C++`
    person(const json::const_iterator & face_it);
   
    /// @brief Converts the data to a json format
    /// @return json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const person & rhs) const;

};
}
}
#endif
