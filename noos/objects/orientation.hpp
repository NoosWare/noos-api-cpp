#ifndef NOOS_OBJECT_ORIENTATION
#define NOOS_OBJECT_ORIENTATION
#include "includes.ihh"
/*
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @struct orientation
 * @brief encapsulate euler angles (roll, pitch, yaw)
 * @version 0.7.3
 * @date 12.07.2017
 */
template <class value_type>
struct orientation
{
    /// coordinates
	value_type roll = 0;
    value_type pitch = 0;
    value_type yaw = 0;

    /// @brief default constructor
    orientation() = default;

    /// @brief Constructor taking roll, pitch and yaw (in radians)
    orientation(value_type roll,
                value_type pitch,
                value_type yaw);

    /// @brief Construct using library "json for modern c++"
    orientation(const json::const_iterator & it);
   
    /// @return a JSON object
    json::object_t to_json() const;
   
    /// @brief Equality operator
    bool operator==(const noos::object::orientation<value_type> & rhs) const;
};
#include "orientation.tpl"
}
}
#endif
