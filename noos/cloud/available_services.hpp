#ifndef NOOS_CLOUD_AVAILABLE_SERVICES
#define NOOS_CLOUD_AVAILABLE_SERVICES
#include "includes.ihh"
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
/*
 * LICENSE HERE
 */
namespace noos {
namespace cloud {
/**
 * @class available_services
 * @brief requests available services from platform
 */
class available_services 
: public http_request,
  public cloud_base<std::vector<std::pair<std::string,
                                          std::string>>>
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
