#ifndef NOOS_OBJECT_POSE
#define NOOS_OBJECT_POSE
#include "includes.ihh"
#include "point.hpp"
#include "orientation.hpp"
/*
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @struct pose
 * @brief Encapsulates position(x, y, z) and orientation(roll, pitch, yaw)
 * @version 0.7.3
 * @date 12.07.2017
 */
template <class value_type>
struct pose
{
    ///Position
    point<value_type> coordinates;
    ///Orientation
	orientation<value_type> angles;

    /// @brief Default constructor
    pose() = default;

    /// @brief Constructor taking a point and an orientation
    pose(point<value_type> coordinates,
         orientation<value_type> angles);

    /// @brief Construct using library "json for modern c++"
    pose(const json::const_iterator & position);
   
    /// @brief Converts the data to a json format
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::pose<value_type> & rhs) const;

    /// @brief Overload operator
    friend std::ostream& operator<<(std::ostream& out, 
                                    const noos::object::pose<value_type>& pose3d)
    {
        //TODO: overload operator << in point and orientation 
        return out << "x: "  << pose3d.coordinates.x
                   << " y: " << pose3d.coordinates.y
                   << " z: " << pose3d.coordinates.z
                   << " roll: " << pose3d.angles.roll
                   << " pitch: " << pose3d.angles.pitch
                   << " yaw: " << pose3d.angles.yaw << std::endl;
    }
 
};

#include "pose.tpl"
}
}
#endif
