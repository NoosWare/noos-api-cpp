#ifndef NOOS_CLOUD_ASIO_HTTP_HEADER
#define NOOS_CLOUD_ASIO_HTTP_HEADER
/*
 * LICENSE HERE
 */
#include <noos/cloud/asio/includes.ihh>
#include <noos/cloud/asio/platform.hpp>
namespace noos {
/// @brief Common cloud namespace
namespace cloud {
/**
 * @class http_header
 * @version 0.7.0
 * @date August 2016
 * @brief Class encapsulates the HTTP Header 1.1 standard
 */
class http_header
{
public:
    /** 
     * @brief Constructor of the http_header
     * @brief Set the \param uri 
     * @warning Requires newline
     */
    http_header(std::string uri);

    /** 
     * @brief Constructor of the http_header
     * @brief Set the \param uri 
     * @warning Requires newline
     * @brief Set \param keep_alive
     */
    http_header(std::string uri, 
                bool keep_alive);

    /**
     * @brief Make this header a `multipart/form-data`
     * @warning It will modify the HTTP Header
     */
    void make_multipart_form();
    
    /**
     * @brief Complete the rest of parameters that we need for the http_header and 
     * @return All of them in a string
     * @param endpoint contains the data of the platform
     * @param length is the size of the content
     */
    std::string to_string(noos::cloud::platform endpoint, unsigned int length);

    /**
     * @brief Get boundary
     * @return Boundary string without they hyphens (--)
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
