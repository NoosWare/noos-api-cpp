#ifndef NOOS_CLOUD_PLATFORM
#define NOOS_CLOUD_PLATFORM
/*
 * LICENSE HERE
 */
#include <string>
#include "includes.ihh"
namespace noos {
/// @brief Common cloud namespace
namespace cloud {
/**
 * @struct platform
 * @version 0.7.2
 * @date 19 December 2016
 * @author Alex Giokas <a.giokas@ortelio.co.uk>
 * @brief Data of the platform where 
 *        you are going to connect
 * @param address is the IP of the platform
 * @param port is the port used in the platform
 * @param token is the password need it to connect
 * @param user is the user need it to connect
 */
struct platform
{
   std::string address;
   std::string port;
   std::string token;
   std::string user;
   std::string protocol;

   /// @brief Deserialise a json to build the platform
   platform operator()(json);

   /// @brief Read a file with a json to build the platform
   platform operator()(std::string filename);
};

/**
 *  @brief Default platform where to connect
 *  @version 0.7.3
 *  @date 05.07.2017
 */
const platform default_node = {"demo.noos.cloud", "9001", "test_token", "test"};

}
}
#endif
