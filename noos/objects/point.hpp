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
    /// coordinate x
	value_type x = 0;
    /// coordinate y
    value_type y = 0;
    /// coordinate z
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

/**
 * @struct point2d
 * @brief encapsulate point of 2 dimensions (x, y)
 * @version 0.8.0
 * @date 28.09.2017
 */
template <class value_type>
struct point2d
{
    /// coordinate x
	value_type x = 0;
    /// coordinate y
    value_type y = 0;

    /// @brief default constructor
    point2d() = default;

    /// @brief constructor taking parameters x and y
    point2d(value_type x_data,
            value_type y_data);

    /// @brief Construct using library "json for modern c++"
    point2d(const json::const_iterator & position);
   
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::point2d<value_type> & rhs) const;
};

/**
 * @struct pose2d
 * @brief encapsulate point of 2 dimensions (x, y) with an angle
 * @version 0.8.0
 * @date 18.10.2017
 */
template <class value_type>
struct pose2d
{
    /// coordinate x
	value_type x = 0;
    /// coordinate y
    value_type y = 0;
    /// angle theta
    value_type theta = 0;

    /// @brief default constructor
    pose2d() = default;

    /// @brief constructor taking parameters x, y and theta
    pose2d(value_type x_data,
           value_type y_data,
           value_type theta_data);

    /// @brief Construct using library "json for modern c++"
    pose2d(const json::const_iterator & position);
   
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::pose2d<value_type> & rhs) const;
};
#include "point.tpl"
}
}
#endif
