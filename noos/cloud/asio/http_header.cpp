#include "http_header.hpp"
namespace noos {
namespace cloud {

http_header::http_header(std::string uri)
: uri_(uri), boundary_(noos::misc::random_boundary())
{
    connection_ = "Connection: close\r\n";
    user_agent_ = "User-Agent: noos_api-cpp-0.7.3\r\n";
}

http_header::http_header(std::string uri,
                         bool keep_alive)
: uri_(uri), 
  boundary_(noos::misc::random_boundary()),
  keep_alive_(keep_alive)
{
    connection_ = "Connection: close\r\n";
    user_agent_ = "User-Agent: noos_api-cpp-0.7.3\r\n";
}

// BUG: make ONLY ONCE
void http_header::make_multipart_form()
{
    content_type_  = "Content-Type: multipart/form-data; boundary=" + boundary_;
}

std::string http_header::to_string(
                                    noos::cloud::platform endpoint, 
                                    unsigned int length
                                  )
{
    std::string host  = "Host: " + endpoint.address + ":" + endpoint.port + "\r\n";
    std::string user  = "User-Token: " + endpoint.user + "\r\n";
    std::string token = "Accept-Token: " + endpoint.token + "\r\n";
    if (length > 0) {
        content_length_	  = "Content-Length: " + boost::lexical_cast<std::string>(length) + "\r\n";
        if (keep_alive_) {
            return uri_ + host + user + token + content_length_ + content_type_ + "\r\n\r\n";
        }
        else {
            return uri_ + host + user + token + connection_ + content_length_ + content_type_ + "\r\n\r\n";
        }
    }
    else {
        if (keep_alive_) 
            return uri_ + host + user + token + "\r\n\r\n";
        else
            return uri_ + host + user + token + connection_+ "\r\n\r\n";
    }
}

std::string http_header::get_boundary() const
{
	return boundary_;
}

}
}
