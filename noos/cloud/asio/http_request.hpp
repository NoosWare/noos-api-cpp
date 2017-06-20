#ifndef NOOS_CLOUD_HTTP_REQUEST
#define NOOS_CLOUD_HTTP_REQUEST
/**
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio.hpp>
#include <noos/cloud/asio/http_header.hpp>
#include <noos/cloud/asio/http_post.hpp>
#include <noos/cloud/asio/platform.hpp>
namespace noos {
namespace cloud {
/**
 * @class http_request
 * @brief wnooser for the classes `http_header` &`http_post` used for cloud requests
 * @version 0.7.0
 * @date 12 August 2016
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 * @see noos::cloud::http_header
 * @see noos::cloud::http_post
 */
class http_request 
{
public:
    /**
	 * @brief construct a cloud HTTP request (multipart/form-data)
	 * @param header will contain the URI and setting the multipart boundary
	 * @param post contains the actual POST data
	 * @see noos::cloud::http_header
	 * @see noos::cloud::http_post
	 */
    http_request(const std::string uri);

    /// copy constructor
    http_request(const http_request & arg);

	/**
     * \brief fill the socket streambuf with the request header and post data
     * \param request is a reference to the socket streambuf being modified
     * \param info is the platform endpoint (address, port, etc)
     * \note this method will modify the header by setting the HOST, PORT and TOKEN
	 * \note use this method to satisfy `virtual caller::fill_buffer` polymorphism
	 */
    void fill_buffer(
                      boost::asio::streambuf & buffer,
                      noos::cloud::platform info
                    );

    /// \brief
    template <typename... Args>
    void add_content(Args... args)
    {
		post_->add_content(std::forward<Args>(args)...);
    }

    /// \brief close this request properly
    void close();

    /// \brief
    std::string to_string(noos::cloud::platform info) const;

    /// \brief
    std::string to_post() const;

    /// brief 
    bool operator==(const http_request & rhs) const;

    /// make this a multipart-form
    void make_multipart_form();

private:
    std::shared_ptr<noos::cloud::http_header> header_;
    std::shared_ptr<noos::cloud::http_post>   post_;
};
}
}
#endif
