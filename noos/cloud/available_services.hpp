#ifndef NOOS_CLOUD_AVAILABLE_SERVICES
#define NOOS_CLOUD_AVAILABLE_SERVICES
#include "includes.ihh"
/**
 *
 * LICENSE HERE
 *
 * @version 0.7.3
 * @date 6 June 2017
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
#include <noos/cloud/asio/http_request.hpp>
namespace noos {
namespace cloud {
/**
 * @class available_services
 * @brief requests available services from platform
 */
class available_services 
: public http_request
{
public:
	using service  = std::pair<std::string,std::string>;
    using callback = std::function<void(std::vector<service>)>;
    static const std::string uri;

    /// @brief construct without any special parameters
    available_services();
};
}
}
#endif
