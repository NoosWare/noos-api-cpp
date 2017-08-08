#ifndef NOOS_OBJECT_HUMAN
#define NOOS_OBJECT_HUMAN
/*
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
namespace object {
/**
 * @class human
 * @brief describes human coordinates
 * @version 0.7.0
 * @date 25 August-2016
 * @author Maria Ramos  <m.ramos@ortelio.co.uk>
 */
struct human
{
    /// coordinates of bounding box
    float top_left_x;
    float top_left_y;
    float bottom_right_x;
    float bottom_right_y;

    /// @brief Constructor using `json for modern C++`
    human(const json::const_iterator & human_it);

    /// @return a json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const human & rhs) const;
   
    /// @brief Method to find component up_left_point in json data
    void up_left_point(const json::const_iterator & coord_it);

    /// @brief Method to find component down_right_point in json data
    void down_right_point(const json::const_iterator & coord_it);
};
}
}
#endif
