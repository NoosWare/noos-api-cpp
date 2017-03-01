#include "cloud_base.hpp"

namespace rapp
{
namespace cloud
{

cloud_base::cloud_base(bool init_value)
: single_callable(init_value)
{}
 
bool cloud_base::is_single_callable() const
{
    return single_callable;
}

std::string cloud_base::make_http_uri(std::string uri) const
{
    return "POST /" + uri + " HTTP/1.1\r\n";
}

}
}
