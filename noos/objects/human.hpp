#ifndef NOOS_OBJECT_HUMAN
#define NOOS_OBJECT_HUMAN
/**
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
class human
{
public:
    /// @brief Construct using coordinates (a rectangle)
    /// @param top_left_x is the coordinate x of top left point
    /// @param top_left_y is the coordinate y of top left point
    /// @param bottom_right_x is the coordinate x of down rigth point   
    /// @param bottom_right_y is the coordinate y of down rigth point
    human( 
          float top_left_x,
          float top_left_y,
          float bottom_right_x,
          float bottom_right_y
        );
   
    /// \brief Allow empty constructor
    human() = default;
    
    /// \brief Copy constructor
    human(const human &) = default;
    
    /// \brief Constructor using `json for modern C++`
    human(const json::const_iterator & human_it);

    /// \return a json object
    json::object_t to_json() const;

    /// \brief Equality operator
    bool operator==(const human & rhs) const;
   
    /// \return top_left_x__ param
    float get_left_x() const;

    /// \return top_left_y__ param
    float get_left_y() const;

    /// \return bottom_right_x__ param
    float get_right_x() const;

    /// \return bottom_right_y__ param
    float get_right_y() const;


private:

    /// \brief Method to find component up_left_point in json data
    void up_left_point(const json::const_iterator & coord_it);

    /// \brief Method to find component down_right_point in json data
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
