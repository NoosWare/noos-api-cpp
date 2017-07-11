#include "laser.hpp"

namespace noos {
namespace object {

json::object_t laser::to_json() const
{
    json::object_t scan_data = {{"aperture", aperture}, 
                                {"timestamp", timestamp},
                                {"max_range", max_range},
                                {"std_error", std_error},
                                {"right_to_left", right_to_left},
                                {"ranges", ranges},
                                {"intensities", intensities},
                                {"valid_range", valid_range},
                                {"sensor_pose", pose.to_json()}
                               };
    return scan_data;
}

}
}
