#ifndef NOOS_OBJECT_FACE
#define NOOS_OBJECT_FACE
/*
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
/// @brief common object namespace
namespace object {
/**
 * @class face
 * @brief describes a face coordinate (cartesian)
 * @version 0.7.3
 * @date 10 June 2017
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct face
{
    /// coordinate x of the top left corner
    float top_left_x;
    /// coordinate y of the top left corner
    float top_left_y;
    /// coordinate x of the bottom right corner
    float bottom_right_x;
    /// coordinate y of the bottom right corner
    float bottom_right_y;

    /// @brief Constructor using `json for modern C++`
    face(const json::const_iterator & face_it);
   
    /// @return json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const face & rhs) const;

    /// @brief Method to find the up_left_point information from json data
    void up_left_point(const json::const_iterator & coord_it);

    /// @brief Method to find the down_right_point information from json data
    void down_right_point(const json::const_iterator & coord_it);
};
}
}
#endif
