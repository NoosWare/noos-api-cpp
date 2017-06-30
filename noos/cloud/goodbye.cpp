#include "goodbye.hpp"

namespace noos {
namespace cloud {
const std::string goodbye::uri = "GET /goodbye HTTP/1.1\r\n";

goodbye::goodbye()
: http_request(uri, false), 
  cloud_base(true)
{}
}
}
