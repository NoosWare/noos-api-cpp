#include "chat.hpp"

namespace noos {
namespace cloud {

//service names
const std::string chatbot::uri = "chat";

chatbot::chatbot(std::string sentence,
                 std::string filename)
: http_request(make_http_uri(uri)),
  cloud_base(true)
{
    http_request::make_multipart_form();
    nlohmann::json json_doc = {{"state", sentence},
                               {"filename", filename}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

}
}
