#ifndef NOOS_CLOUD_CHAT
#define NOOS_CLOUD_CHAT
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/objects.hpp>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
namespace noos {
namespace cloud {
/**
 * @struct chatbot
 * @brief Reply the sentence sent
 * @version 0.9.0
 * @note data type passed back is `std::string`
 */
struct chatbot 
: public http_request, 
  public cloud_base<std::string>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    /// @brief Constructor using an std::string with a sentence
    chatbot(std::string sentence,
            std::string filename = "");

};
}
}
#endif
