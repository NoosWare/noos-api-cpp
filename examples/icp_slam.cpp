#include <noos/noos>
#include <iostream>
#include <chrono>
/*
 * \brief Example to do 2D mapping with laser data
 */
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
     * The next parameters are needed:
     * @param noos::object::config_file is the configuration file
     * @param noos::cloud::slam_type. Due to there are different methods
     *                          for doing slam, it's needed to specify it.
     */
    auto config = noos::object::config_file("data/config_file.ini");

    auto request  = upload_config_file(config, noos::cloud::slam_type::icp);
    auto config_callback = [](bool success) {
        std::cout << "Success uploading the config file: " << std::boolalpha << success << std::endl;
    };

    /*
     * Finally we create a callable object and send the information to the platform
     * with a timeout of 2 seconds
     * For more information /see noos::cloud::callable
     *
     * The actual parameter depends on the cloud class you're using,
     * so for a complete list, you need to read and understand how each cloud class functions.
     */
    callable<upload_config_file> config_callable(request, config_callback);
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
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a noos::object::pose with the position
     * of the robot
     */
    auto icp_request = icp_slam("map_name", 100, laser);
    auto callback = [&](noos::object::pose<float> pose3d) {
        std::cout << pose3d;
    };

    /*
     * We make a callable object of qr_recognition class to detect qr_codes in the file
     * and we send the information to the platform.
     * For more information \see noos::cloud::qr_recognition
     */
    callable<icp_slam,true> callable_icp(icp_request, callback);
    for (auto i = 0; i < 1500; i++) {
        callable_icp.send();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
