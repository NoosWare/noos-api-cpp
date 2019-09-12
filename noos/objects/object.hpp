#ifndef NOOS_OBJECT_OBJECT
#define NOOS_OBJECT_OBJECT
/*
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
/// @brief Common object namespace
namespace object {
/**
 * @class object
 * @brief Describes a object coordinate (cartesian)
 * @version 1.0.0
 * @date 18.04.2019
 */
struct object
{
    /// Coordinate x of the top left corner
    float top_left_x;
    /// Coordinate y of the top left corner
    float top_left_y;
    /// Coordinate x of the bottom right corner
    float bottom_right_x;
    /// Coordinate y of the bottom right corner
    float bottom_right_y;
    ///Name of the object found
    std::string label;
    ///Confidence [0,1]
    float confidence;

    /// @brief Constructor using `json for modern C++`
    object(const json::const_iterator & object_it);
   
    /// @brief Equality operator
    bool operator==(const object & rhs) const;

    /// @brief Method to find the up_left_point information from json data
    void up_left_point(const json::const_iterator & coord_it);

    /// @brief Method to find the down_right_point information from json data
    void down_right_point(const json::const_iterator & coord_it);
};
}
}
#endif
