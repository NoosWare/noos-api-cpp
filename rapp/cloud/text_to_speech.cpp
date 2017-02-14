#include "text_to_speech.hpp"
namespace rapp 
{
namespace cloud 
{

const std::string text_to_speech::text_to_speech_post__ = "POST /hop/text_to_speech HTTP/1.1\r\n";

text_to_speech::text_to_speech(
                                const std::string text,
                                const std::string language,
                                std::function<void(audio_file)> callback
                              )
: http_request(text_to_speech_post__), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"text", text},
                     {"language", language}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void text_to_speech::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    if(misc::check_json(json_f, json)) {
        std::vector<rapp::types::byte> bytearray;
        std::string decoded = rapp::misc::decode64(json_f["payload"]);
        std::copy(decoded.begin(), decoded.end(), std::back_inserter(bytearray));
        delegate_(rapp::object::audio(bytearray));
    }
}

}
}
