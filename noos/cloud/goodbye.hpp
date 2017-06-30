#ifndef NOOS_CLOUD_GOODBYE
#define NOOS_CLOUD_GOODBYE
/**
 * LISENSE HERE
 */
#include "includes.ihh"
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
namespace noos {
namespace cloud {
/**
 * @struct goodbye
 * @brief close connections
 * @version 0.7.3
 * @date 30.06.2017
 */
struct goodbye 
: public http_request, 
  public cloud_base<std::string>
{
    using callback = std::function<void(std::string)>; 
    static const std::string uri;

    /// @brief empty ctor used by vision batch
    goodbye();
};
}
}
#endif
