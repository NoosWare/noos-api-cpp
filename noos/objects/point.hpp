#ifndef NOOS_OBJECT_POINT
#define NOOS_OBJECT_POINT
#include "includes.ihh"
/*
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @struct point
 * @brief encapsulate point position vector
 * @version 0.7.0
 * @date 19 August 2016
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
template <class value_type>
struct point
{
    /// coordinates
	value_type x = 0;
    value_type y = 0;
    value_type z = 0;

    /// @brief default constructor
    point() = default;

    /// @brief constructor taking parameters x, y and z
    point(value_type x_data,
          value_type y_data,
          value_type z_data);

    /// @brief Construct using library "json for modern c++"
    point(const json::const_iterator & position);
   
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::point<value_type> & rhs) const;
};
#include "point.tpl"
}
}
#endif
