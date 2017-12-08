#include "odometry.hpp"

namespace noos {
namespace object {

json::object_t odometry::to_json() const
{
    json::object_t increment = {{"inc_lin_x", inc_x}, 
                                {"inc_lin_y", inc_y},
                                {"inc_ang", inc_yaw}
                               };
    return increment;
}

bool odometry::operator==(const noos::object::odometry & rhs) const
{
   return ((this->inc_x == rhs.inc_x) &&
           (this->inc_y == rhs.inc_y) &&
           (this->inc_yaw == rhs.inc_yaw));
}

}
}
