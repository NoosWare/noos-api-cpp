#ifndef NOOS_CLOUD_NAVIGATION
#define NOOS_CLOUD_NAVIGATION
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/objects.hpp>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
namespace noos {
namespace cloud {
/**
 * TODO:think another name for the class
 * @struct icp_slam
 * @brief detect faces in the image
 */
struct icp_slam 
: public http_request, 
  public cloud_base<noos::object::pose<float>>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @param laser_data is the laser reading
    icp_slam(const noos::object::laser & laser_data);

    /// TODO:overload constructor with 3d data(pointcloud)
};

}
}
#endif
