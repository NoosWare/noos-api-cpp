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
 * @struct icp_slam
 * @brief send laser/pointcloud data to create a map
 * @version 0.8.0
 * @date 30.08.2017
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

/**
 * @struct delete map
 * @brief delete a map saved in the platform
 * @version 0.8.0
 * @date 30.08.2017
 */
struct delete_map 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @param laser_data is the laser reading
    delete_map(const std::string name);
};

/**
 * @struct upload_map
 * @brief upload a map to the platform
 * @version 0.8.0
 * @date 30.08.2017
 */
struct upload_map 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @param laser_data is the laser reading
    upload_map(const std::string name,
               const noos::object::picture & image);
};

}
}
#endif
