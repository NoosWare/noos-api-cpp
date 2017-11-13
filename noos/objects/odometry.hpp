#ifndef NOOS_OBJECT_ODOMETRY
#define NOOS_OBJECT_ODOMETRY
/*
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
/// @brief common object namespace
namespace object {
/**
 * @struct odometry
 * @brief describes the increment of the odometry
 * @version 0.8.0
 * @date 16.09.2017
 */
struct odometry
{
    /// increment in x coordinates(in meters)
    float inc_x;
    /// increment in y coordinates(in meters)
    float inc_y;
    /// increment in yaw(in degrees)
    float inc_yaw;
   
    /// @return json object
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const noos::object::odometry & rhs) const;
};
}
}
#endif
