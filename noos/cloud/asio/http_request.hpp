#ifndef NOOS_CLOUD_HTTP_REQUEST
#define NOOS_CLOUD_HTTP_REQUEST
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio.hpp>
#include <noos/cloud/asio/http_header.hpp>
#include <noos/cloud/asio/http_post.hpp>
#include <noos/cloud/asio/platform.hpp>
namespace noos {
/// @brief Common cloud namespace
namespace cloud {
/**
 * @class http_request
 * @brief Nooser for the classes `http_header` & `http_post` used for cloud requests
 * @version 0.7.3
 * @date 12 August 2016
 */
class http_request 
{
public:
    /// @brief Construct a cloud HTTP request (multipart/form-data)
    http_request(const std::string uri);

    /// @brief Construct a cloud HTTP request (multipart/form-data)
    ///        with keep_alive param
    http_request(const std::string uri,
                 bool keep_alive);

    /// @brief Copy constructor
    http_request(const http_request & arg);

    /**
     * @brief Fill the socket streambuf with the request header and post data
     * @param request is a reference to the socket streambuf being modified
     * @param info is the platform endpoint (address, port, etc)
     * @note this method will modify the header by setting the HOST, PORT and TOKEN
     * @note use this method to satisfy `virtual caller::fill_buffer` polymorphism
     */
    void fill_buffer(
                      boost::asio::streambuf & buffer,
                      noos::cloud::platform info
                    );

    /// @brief Add multiple content to the post with
    ///        HTTP Protocol 
    template <typename... Args>
    void add_content(Args... args);

    /// @brief Close this request properly
    /// @warning A non-closed HTTP request is an illegal one!
    void close();

    /// @brief Translate noos::cloud::platform parameters
    ///        into a string with HTTP Protocol format
    std::string to_string(noos::cloud::platform info) const;

    /// @brief Translate post data into a string
    ///        with HTTP Protocol format    
    std::string to_post() const;

    /// @brief Compare if two http_request are equal
    bool operator==(const http_request & rhs) const;

    /// @brief Make this a multipart-form, by creating
    /// the correct header fields, boundaries and multipart entries
    void make_multipart_form();

private:
    std::shared_ptr<noos::cloud::http_header> header_;
    std::shared_ptr<noos::cloud::http_post>   post_;
};
}
}
#include "http_request.tpl"
#endif
