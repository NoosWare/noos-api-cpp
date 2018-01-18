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
 * @brief Encapsulate point of 3 dimensions
 * @version 0.7.0
 * @date 19 August 2016
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
template <class value_type>
struct point
{
    /// Coordinate x
	value_type x = 0;
    /// Coordinate y
    value_type y = 0;
    /// Coordinate z
    value_type z = 0;

    /// @brief Default constructor
    point() = default;

    /// @brief Constructor taking parameters x, y and z
    point(value_type x_data,
          value_type y_data,
          value_type z_data);

    /// @brief Construct using library "json for modern c++"
    point(const json::const_iterator & position);
   
    /// @brief Converts the data to a json format
    /// @return A JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::point<value_type> & rhs) const;
};

/**
 * @struct point2d
 * @brief Encapsulate point of 2 dimensions (x, y)
 * @version 0.8.0
 * @date 28.09.2017
 */
template <class value_type>
struct point2d
{
    /// Coordinate x
	value_type x = 0;
    /// Coordinate y
    value_type y = 0;

    /// @brief Default constructor
    point2d() = default;

    /// @brief Constructor taking parameters x and y
    point2d(value_type x_data,
            value_type y_data);

    /// @brief Construct using library "json for modern c++"
    point2d(const json::const_iterator & position);
   
    /// @brief Converts the data to a json format
    /// @return A JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::point2d<value_type> & rhs) const;
};

/**
 * @struct pose2d
 * @brief Encapsulate point of 2 dimensions (x, y) with an angle
 * @version 0.8.0
 * @date 18.10.2017
 */
template <class value_type>
struct pose2d
{
    /// Coordinate x
	value_type x = 0;
    /// Coordinate y
    value_type y = 0;
    /// Angle theta
    value_type theta = 0;

    /// @brief Default constructor
    pose2d() = default;

    /// @brief Constructor taking parameters x, y and theta
    pose2d(value_type x_data,
           value_type y_data,
           value_type theta_data);

    /// @brief Construct using library "json for modern c++"
    pose2d(const json::const_iterator & position);
   
    /// @brief Converts the data to a json format
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::pose2d<value_type> & rhs) const;
};
#include "point.tpl"
}
}
#endif
