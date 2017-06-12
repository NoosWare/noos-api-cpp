#ifndef NOOS_OBJECT_FACE
#define NOOS_OBJECT_FACE
/**
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
namespace object {
/**
 * @class face
 * @brief describes a face coordinate (cartesian)
 * @version 0.7.3
 * @date 10 June 2017
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face
{
public:
    /// @brief Construct using face coordinates (a rectangle)
    /// @param top_left_x is the coordinate x of top left point
    /// @param top_left_y is the coordinate y of top left point
    /// @param bottom_right_x is the coordinate x of down right point
    /// @param bottom_right_y is the coordinate y of down right point
    face( 
          float top_left_x,
          float top_left_y,
          float bottom_right_x,
          float bottom_right_y
        );
  
    /// @brief Allow empty constructor
    face() = default;
    
    /// @brief Copy constructor
    face(const face &) = default;

    /// @brief Constructor using `json for modern C++`
    face(const json::const_iterator & face_it);
   
    /// @return json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const face & rhs) const;
    
    /// @return top_left_x__ param
    float get_left_x() const;

    /// @return top_left_y__ param
    float get_left_y() const;

    /// @return bottom_right_x__ param
    float get_right_x() const;

    /// @return bottom_right_y__param
    float get_right_y() const;

private:

    /// @brief Method to find the up_left_point information from json data
    void up_left_point(const json::const_iterator & coord_it);

    /// @brief Method to find the down_right_point information from json data
    void down_right_point(const json::const_iterator & coord_it);

    /// members
    float top_left_x__;
    float top_left_y__;
    float bottom_right_x__;
    float bottom_right_y__;
};
}
}
#endif
