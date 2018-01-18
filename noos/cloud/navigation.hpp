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
 * @brief Enum class to clasify types of slam (icp or rbpf)
 * @enum slam_type
 * @version 0.8.0
 * @date 1.09.2017
 */
enum class slam_type
{
    not_selected = 0,
    icp,
    rbpf
};

/**
 * @struct icp_slam
 * @brief Send laser/pointcloud data to create a map
 * @version 0.8.0
 * @date 30.08.2017
 * @note data type passed back is `noos::object::pose<float>`
 */
struct icp_slam 
: public http_request, 
  public cloud_base<noos::object::pose<float>>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /**
     * @brief Constructor using the following parameters:
     * @param laser_data is the laser reading
     * @param map_name is the name of the map where the data
     *        is going to be saved. 
     * @warning DON'T WRITE THE EXTENSION. All the maps will 
     *          be `.png` 
     * @param config_file_name is the name of the config file
     *        which is going to be loaded in the platform
     * @see noos::object::laser
     */
    icp_slam(const std::string map_name,
             const std::string config_file_name,
             const noos::object::laser laser_data);

    // TODO:overload constructor with 3d data(pointcloud)
};

/**
 * @struct rbpf_slam
 * @brief Send laser/pointcloud data and odometry to create a map
 * @version 0.8.0
 * @date 16.09.2017
 * @note data type passed back is `noos::object::pose<float>`
 */
struct rbpf_slam 
: public http_request, 
  public cloud_base<noos::object::pose<float>>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /**
     * @brief Constructor using the following parameters:
     * @param laser_data is the laser reading
     * @param map_name is the name of the map where the data
     *        is going to be saved. 
     * @Warning DON'T WRITE THE EXTENSION. All the maps will 
     *          be .png 
     * @param config_file_name is the name of the config file
     *        which is going to be loaded in the platform
     * @param odometry is the increment of the odometry between the 
     *        previous and the next laser reading.
     * @see noos::object::laser  
     * @see noos::object::odometry
     */
    rbpf_slam(const std::string map_name,
              const std::string config_file_name,
              const noos::object::laser laser_data,
              const noos::object::odometry & odometry);

    // TODO:overload constructor with 3d data(pointcloud)
};

/**
 * @struct delete_map
 * @brief Delete a map saved in the platform
 * @version 0.8.0
 * @date 30.08.2017
 * @note data type passed back is `bool`
 */
struct delete_map 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @brief Constructor using the map name
    /// @param name is the name of the map
    /// @warning the name must not contain any extension
    delete_map(const std::string name);
};

/**
 * @struct upload_map
 * @brief Upload a map to the platform
 * @version 0.8.0
 * @date 30.08.2017
 * @note data type passed back is `bool`
 */
struct upload_map 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @brief Constructor using the map name and the image 
    ///        of the map
    /// @param name of the map (without extension)
    /// @param image the map
    /// @warning DON'T WRITE THE EXTENSION. All the maps will 
    ///         be `.png` 
    /// @see noos::object::picture
    upload_map(const std::string name,
               const noos::object::picture & image);
};

/**
 * @struct upload_slam_config_file
 * @brief Upload a config_file with SLAM parameters to the platform
 * @version 0.8.0
 * @date 01.09.2017
 * @note data type passed back is `bool`
 */
struct upload_slam_config_file 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    static std::map<slam_type, std::string> config_type;


    /**
     * @brief Constructor using the following parameters:
     * @param file is the config file to upload
     * @param name is the name that the file will have in
     *         the platform
     * @param type the type of slam 
     * @see `slam_type`
     */
    upload_slam_config_file(noos::object::config_file & file,
                            std::string name,
                            slam_type type);
};

/**
 * @struct get_map
 * @brief Get the image of the map name asked for
 * @version 0.8.0
 * @date 04.09.2017
 * @note data type passed back is `bool`
 */
struct get_map 
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    static std::map<slam_type, std::string> config_type;

    /// @brief Constructor using the map name
    /// @param map_name is the name of the map (without extension)
    get_map(std::string map_name);
};

/**
 * @struct path_planning
 * @brief Calculate a path between two points given
 * @version 0.8.0
 * @date 17.10.2017
 * @note data type passed back is `std::deque<noos::object::point2d<float>>`
 */
struct path_planning 
: public http_request, 
  public cloud_base<std::deque<noos::object::point2d<float>>>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /**
     * @brief Constructor using the following parameters: 
     * @param start is the start point of the robot
     * @param goal is the goal pose where you need to go
     * @param robot_radius is the radius in meters of the robot
     * @param resolution is the resolution that the map has
     * @param map_name is the name of the map (without extension)
     * @warning DON'T WRITE THE EXTENSION. All the maps will 
     *          be `.png` 
     */
    path_planning(const noos::object::pose2d<float> start,
                  const noos::object::pose2d<float> goal,
                  const float robot_radius,
                  const float resolution,
                  const std::string map_name);
};
}
}
#endif
