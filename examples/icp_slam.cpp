#include <noos/noos>
#include <iostream>
#include <chrono>

// TODO: REMOVE THIS EXAMPLE

/// \brief function to read a json file and it is converted 
//  into a string param
std::string read_json_file(const std::string file)
{
    if (file.empty()){
        throw std::runtime_error("empty file param");
    }
    std::ifstream t(file);
    if (t.good()) {
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();
	return buffer.str();
    }
    else {
        throw std::runtime_error("failed to open ifsteam");
    }
}

int main()
{
    using namespace noos::cloud;
    /*
     * Before starting slam, a configuration file has to be sent
     * to the platform. It's required only once.
     */
    auto config = noos::object::config_file("data/config_file.ini");
    auto request  = upload_slam_config_file(config, "icp.ini", noos::cloud::slam_type::icp);
    auto config_callback = [](bool success) {
        std::cout << "Success uploading the config file: " << std::boolalpha << success << std::endl;
    };
    /*
     * Finally we create a callable object and send the information to the platform
     * with a timeout of 2 seconds
     * For more information /see noos::cloud::callable
     */
    auto config_callable = call<upload_slam_config_file,false>(config_callback, 
                                                               config,
                                                               "icp.ini",
                                                               slam_type::icp);
    config_callable.send();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    /*
     * Now, the SLAM part
     * First, the laser data is filled to allow do the mapping
     * For more information \see noos::object::laser
     */
    std::string string = read_json_file("data/cloud_class_laser_data.json");
    auto json = nlohmann::json::parse(string);
    std::vector<float> laser_ranges = json["ranges"];
    std::vector<int> laser_intensities = json["intensities"];
    noos::object::laser laser;
    laser.ranges = laser_ranges;
    laser.intensities = laser_intensities;
    laser.aperture = 4.71239; //270 degrees
    laser.max_range = 10.0f;
    laser.std_error = 0.02;
    laser.right_to_left = true;
    laser.timestamp = 0;
    laser.pose3d = noos::object::pose<float>(); 
    /*
     * Construct a lambda, std::function or bind your own functor.
     */
    auto icp_request = icp_slam("map_name", "icp.ini", laser);
    auto callback = [&](noos::object::pose<float> pose3d) {
        std::cout << pose3d;
    };
    /*
     * We make a callable object of qr_recognition class to detect qr_codes in the file
     * and we send the information to the platform.
     * For more information \see noos::cloud::icp_slam
     */
    auto callable_icp = call<icp_slam,false>(callback, "map_name", "icp.ini", laser);
    for (auto i = 0; i < 1500; i++) {
        callable_icp.send();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
