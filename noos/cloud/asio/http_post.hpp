#ifndef NOOS_CLOUD_ASIO_HTTP_POST
#define NOOS_CLOUD_ASIO_HTTP_POST
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/objects/globals.hpp>
namespace noos {
/// @brief Common cloud namespace
namespace cloud {
/**
 * @class http_post 
 * @brief Use to store and pass POST data and realted info  
 * @version 0.7.0
 * @date August 2016
 */
class http_post
{
public:
    /**
     * @brief Preferred constructor
     * @param boundary must be obtained from `http_header::get_boundary()` 
     * @see http_header
     */
    http_post(std::string boundary);
    
    /**
     * @brief Add multipart/form-data content to the POST data
     * @param name of the form
     * @param content is the value
     * @param newline adds newline return at the end of content
     */
    void add_content(
                      const std::string name, 
                      const std::string content,
                      bool newline
                    );

    /**
     * @brief Adding content to the POST data
     * @param name is the name of the string variable
     * @param filename which want to use
     * @param vector contains the data of the file in binary type  
     * @warning it will add newline return after the bytes
     * @see noos::types::byte
     */
    void add_content(
                      const std::string name,
                      const std::string filename,
                      const std::vector<noos::types::byte> bytes
                    );
       
    /// @brief Call once, closes the POST boundary
    void end();

    /// @brief Get the POST
    std::string to_string() const;

    /// @brief Get POST data `Content-Length`
    unsigned int size() const;

private:
    std::string data_;
    std::string boundary_;
    std::atomic<bool> open_ = {true};
};
}
}
#endif
