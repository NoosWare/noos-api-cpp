#include "navigation.hpp"
namespace noos {
namespace cloud {

//service names
const std::string icp_slam::uri = "icp_slam";

//Class icp_slam 
icp_slam::icp_slam(const noos::object::laser & laser_data)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"laser", laser_data.to_json()}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

}
}
