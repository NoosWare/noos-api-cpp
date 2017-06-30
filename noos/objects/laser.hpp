#ifndef NOOS_OBJECT_LASER
#define NOOS_OBJECT_LASER
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include "noos/objects/point.hpp"
namespace noos {
/// @brief common object namespace
namespace object {
/**
 * @class laser
 * @brief describes a laser scan data 
 * @version 0.7.3
 * @date 27 June 2017
 */
struct laser
{
    /// members
    /// Aperture of the laser in radians
    float aperture;
    /// Time
    uint64_t timestamp;
    /// Maximum distance of laser measurements in meters
    float max_range;
    /// Statistical error of laser
    float std_error;
    /// The direction in which the laser rotates
    bool right_to_left;
    /// Measurements of distance
    std::vector<float> ranges;
    /// Intensity values of the scan
    std::vector<int> intensities;
    /// Check if measurements are valid
    std::vector<char> valid_range;
    /// Sensor pose
    point<float> pose;

    /// @brief Constructor 
    laser() = default;
   
    /// @return json object
    json::object_t to_json() const;

};
}
}
#endif
