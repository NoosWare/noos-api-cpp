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
 * @brief class to clasify types of slam
 * @class slam_type
 * @version 0.2.0
 * date 1.09.2017
 */
enum class slam_type
{
    not_selected = 0,
    icp,
    rbpf
};

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

    /**
     * @param laser_data is the laser reading
     * @param map_name is the name of the map where the data
     *        is going to be saved. 
     * @Warning DON'T WRITE THE EXTENSION. All the maps will 
     *          be .png 
     * @param iteration is when the map is going to be saved
     *        (every 10 iterations, 100, 200, etc.)
     */
    icp_slam(const std::string map_name,
             const int iteration,
             const noos::object::laser & laser_data);

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

/**
 * @struct upload_config_file
 * @brief upload a config file to the platform
 * @version 0.8.0
 * @date 01.09.2017
 */
struct upload_config_file 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    static std::map<slam_type, std::string> config_type;

    /// @param laser_data is the laser reading
    upload_config_file(noos::object::config_file & file,
                       slam_type type);
};

/**
 * @struct get_map
 * @brief get the image of the map name asked for
 * @version 0.8.0
 * @date 04.09.2017
 */
struct get_map 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    static std::map<slam_type, std::string> config_type;

    /// @param laser_data is the laser reading
    get_map(std::string map_name);
};

}
}
#endif
