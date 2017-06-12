#include "http_header.hpp"
namespace rapp {
namespace cloud {

http_header::http_header(std::string uri)
: uri_(uri), boundary_(rapp::misc::random_boundary())
{
    connection_ = "Connection: close\r\n";
	user_agent_ = "User-Agent: rapp_api-cpp-0.7.3\r\n";
}

// BUG: make ONLY ONCE
void http_header::make_multipart_form()
{
	content_type_  = "Content-Type: multipart/form-data; boundary=" + boundary_;
}

std::string http_header::to_string(
                                    rapp::cloud::platform endpoint, 
                                    unsigned int length
                                  )
{
	std::string host  = "Host: " + endpoint.address + ":" + endpoint.port + "\r\n";
    std::string user  = "User-Token: " + endpoint.user + "\r\n";
	std::string token = "Accept-Token: " + endpoint.token + "\r\n";
    if (length > 0) {
	    content_length_	  = "Content-Length: " + boost::lexical_cast<std::string>(length) + "\r\n";
        if (!keep_alive_) {
            return uri_ + 
                   host + 
                   connection_ +
                   user + 
                   token + 
                   content_length_ + 
                   content_type_ + 
                   "\r\n\r\n";
        }
        else {
            return uri_ + 
                   host + 
                   user + 
                   token + 
                   content_length_ + 
                   content_type_ + 
                   "\r\n\r\n";
        }
    }
    else {
        return uri_ + host + user + token + "\r\n\r\n";
    }
}

std::string http_header::get_boundary() const
{
	return boundary_;
}

void http_header::set_keep_alive(bool keep_alive)
{
    keep_alive_ = keep_alive;
}

}
}
