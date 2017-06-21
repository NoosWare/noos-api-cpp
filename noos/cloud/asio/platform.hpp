#ifndef NOOS_CLOUD_PLATFORM
#define NOOS_CLOUD_PLATFORM
/**
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
 * @brief use to construct a service controller with correct params
 *
 * TODO: add better documentation
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
}
}
#endif
