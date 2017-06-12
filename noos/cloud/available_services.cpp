#include "available_services.hpp"
namespace noos {
namespace cloud {
available_services::available_services()
: http_request("GET /available_services HTTP/1.1\r\n")
{}
}
}
