#ifndef NOOS_CLOUD_HTTP_RESPONSE
#define NOOS_CLOUD_HTTP_RESPONSE
/*
 * LICENSE HERE
 */
#include <noos/cloud/asio/includes.ihh>
#include <boost/asio.hpp>
namespace noos {
/// @brief common cloud namespace
namespace cloud {
typedef boost::system::error_code error_code;

/**
 * @brief show the specific error due to a protocol error
 * @struct protocol_errors
 * @version 0.8.1
 * @date 25.10.2017
 */
struct protocol_errors
{
    /// @brief operator which translates HTTP code errors
    //         to boost::system::error_code
    error_code operator()(unsigned int status_code);
};

/**
 * @class http_response
 * @version 0.7.0
 * @date 12 August 2016 
 * @brief class for taking the body of the streambuf , in other case
 *        it will return an error
 * @note The defined error callback may receive the following errors:
 *          - boost::system::errc::bad_message if the header is not followed by a double return carriage
 *          - boost::system::errc::no_message if the platform does not respond with any data
 *          - boost::system::errc::protocol_not_supported if the reply does not conform to HTTP 1.1
 *          - boost::system::errc::protocol_error if HTTP header does not respond with 200 status code
 */
class http_response
{
public:
	/**
	 * @brief construct a response object by setting the error receiver callback
	 * @param callback will receive errors
	 */
    http_response(std::function<void(error_code error)> callback);
    
    /// constructor only for unit testing
    http_response(std::string arg);

    /** 
	 * @brief get the content length streambuf response
     * @return content-length or -1 for not found
	 */
    unsigned int content_length();

    /// @brief remove/strip the HTTP header and \return the body
    unsigned int strip_http_header(unsigned int bytes);
    
    /// @brief conversion from streambuf to string
    std::string to_string();

    /// @get total POST data bytes received
    unsigned int bytes_received() const;
    
    /** 
	 * @brief check if HTTP status is 200
	 * @param error handler will receive error if response is invalid
	 */
    bool check_http_header();
         
	/// @brief take data from the response and save it in JSON
	bool consume_buffer(std::function<void(std::string)> callback, 
                        unsigned int bytes);
	
	/// @brief clean the variables
	void flush_data();
    	
protected:
    boost::asio::streambuf buffer_;
    std::string reply_string;
private:
    std::function<void(error_code error)> error_cb_;
    unsigned int bytes_transferred_ = 0;
    unsigned int content_length_ = 0;
    std::atomic<bool> once_ = {false};
};
}
}
#endif
