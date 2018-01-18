#ifndef NOOS_OBJECT_ODOMETRY
#define NOOS_OBJECT_ODOMETRY
/*
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
/// @brief Common object namespace
namespace object {
/**
 * @struct odometry
 * @brief Describes the increment of the odometry
 * @version 0.8.0
 * @date 16.09.2017
 */
struct odometry
{
    /// Increment in x-coordinate(in meters)
    float inc_x;
    /// Increment in y-coordinate(in meters)
    float inc_y;
    /// Increment in yaw angle(in degrees)
    float inc_yaw;
   
    /// @brief Converts the data to a json format
    /// @return json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const noos::object::odometry & rhs) const;
};
}
}
#endif
