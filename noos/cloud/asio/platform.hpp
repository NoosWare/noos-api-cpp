#ifndef NOOS_CLOUD_PLATFORM
#define NOOS_CLOUD_PLATFORM
/*
 * LICENSE HERE
 */
#include <string>
#include "includes.ihh"
namespace noos {
namespace cloud {
/**
 * @struct platform
 * @version 0.7.2
 * @date 19 December 2016
 * @author Alex Giokas <a.giokas@ortelio.co.uk>
 * @brief data of the platform where 
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

   /// @brief deserialise a json to build the platform
   platform operator()(json);

   /// @brief read a file with a json to build the platform
   platform operator()(std::string filename);
};

/**
 *  @brief default platform where to connect
 *  @version 0.7.3
 *  @date 05.07.2017
 */
///TODO: change uri to "free.noos.io" or "free.noos.cloud"
const platform default_node = {"127.0.0.1", "8080", "test_token", "test"};

/**
 *  @brief european platform
 *  @version 0.7.3
 *  @date 05.07.2017
 */
const platform eu_node = {"10.130.3.17", "8080", "mysecret", "alex"};

}
}
#endif
