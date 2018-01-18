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
 * @brief Requests available services from platform
 * @version 0.8.0
 * @note data type passed back is `std::vector<std::string>`
 */
class available_services 
: public http_request,
  public cloud_base<std::vector<std::string>>
{
public:
    using callback = std::function<void(std::vector<std::string>)>;
    static const std::string uri;

    /// @brief Construct without any special parameters
    available_services();
};
}
}
#endif
