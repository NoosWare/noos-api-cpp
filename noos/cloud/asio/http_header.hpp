#ifndef NOOS_CLOUD_ASIO_HTTP_HEADER
#define NOOS_CLOUD_ASIO_HTTP_HEADER
/*
 * LICENSE HERE
 */
#include <noos/cloud/asio/includes.ihh>
#include <noos/cloud/asio/platform.hpp>
namespace noos {
/// @brief common cloud namespace
namespace cloud {
/**
 * @class http_header
 * @version 0.7.0
 * @date August 2016
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 * @brief class encapsulates the HTTP Header 1.1 standard
 */
class http_header
{
public:
    /** 
     * @brief constructor of the http_header
     * @brief set the \param uri 
     * @warning requires newline
     */
    http_header(std::string uri);

    /** 
     * @brief constructor of the http_header
     * @brief set the \param uri 
     * @warning requires newline
     * @brief set \param keep_alive
     */
    http_header(std::string uri, 
                bool keep_alive);

    /**
     * @brief make this header a `multipart/form-data`
     * @warning it will modify the HTTP Header
     */
    void make_multipart_form();
    
    /**
     * @brief complete the rest of parameters that we need for the http_header and 
     * @return all of them in a string
     * @param endpoint contains the data of the platform
     * @param length is the size of the content
     */
    std::string to_string(noos::cloud::platform endpoint, unsigned int length);

    /**
     * @brief get boundary
     * @return boundary string without they hyphens (--)
     */
    std::string get_boundary() const;

private:    
    std::string uri_;
    std::string user_agent_;
    std::string connection_;
    std::string content_length_;
    std::string content_type_;
    std::string boundary_;
    std::atomic<bool> keep_alive_ = {true};
};
}
}
#endif
