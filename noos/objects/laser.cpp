#include "laser.hpp"

namespace noos {
namespace object {


json::object_t laser::to_json() const
{
    assert(!ranges.empty());
    assert(!intensities.empty());
    if (ranges.size() <= 0) {
        throw std::runtime_error("invalid ranges");
    }
    if (intensities.size() <= 0) {
        throw std::runtime_error("invalid intensities");
    }
    json::object_t scan_data = {{"aperture", aperture}, 
                                {"timestamp", timestamp},
                                {"max_range", max_range},
                                {"std_error", std_error},
                                {"right_to_left", right_to_left},
                                {"ranges", ranges},
                                {"intensities", intensities},
                                {"sensor_pose", pose3d.to_json()}
                               };
    return scan_data;
}

bool laser::operator==(const noos::object::laser & rhs) const
{
   return ((this->aperture      == rhs.aperture) &&
           (this->timestamp     == rhs.timestamp) &&
           (this->max_range     == rhs.max_range) &&
           (this->std_error     == rhs.std_error) &&
           (this->right_to_left == rhs.right_to_left) &&
           (this->ranges        == rhs.ranges) &&
           (this->intensities   == rhs.intensities) &&
           (this->pose3d        == rhs.pose3d));
}

}
}
