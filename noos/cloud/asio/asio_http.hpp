#ifndef NOOS_CLOUD_ASIO_HTTP
#define NOOS_CLOUD_ASIO_HTTP
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio.hpp>
#include <noos/cloud/asio/asio_handler.hpp>
namespace noos {
/// @brief Common cloud namespace
namespace cloud {
/**
 * @class asio_http
 * @brief ASIO socket controller asynchronous http websockets used for cloud service calls
 * @version 0.7.2
 * @date 15 December 2016
 * @author Alex Giokas  <a.gkiokas@ortelio.co.uk>
 * @see asio_handler
 * @see http_request
 * @see http_response
 */
class asio_http 
: public asio_handler<http_socket, asio_http>
{
public:
    /**
 	 * @brief Constructor
	 * @param cloud_function is the virtual `json_parser::deserialize` receiving the data
	 * @param error_function is the handler which may receive the errors
	 * @param io_service is the ASIO service controller
	 * @param request is a stream buffer containing the request
	 */
    asio_http(
                std::function<void(std::string)> cloud_callback,
                std::function<void(error_code)> error_callback,
                boost::asio::io_service & io_service,
                const bool keep_alive,
                boost::asio::streambuf & request
             );

	/**
	 * @brief Begin connection
	 * @param query defines the URL/URI
	 * @param resolver resolves the URL/URI address
     * @param io_service is the queue on which jobs are scheduled
	 */
	void begin(
                boost::asio::ip::tcp::resolver::query & query,
                boost::asio::ip::tcp::resolver & resolver,
                unsigned int timeout
              );

	/**
	 * @brief Send data in an existing connection
	 * @param query defines the URL/URI
	 * @param resolver resolves the URL/URI address
     * @param io_service is the queue on which jobs are scheduled
	 */
    void send(
                boost::asio::ip::tcp::resolver::query & query,
                boost::asio::ip::tcp::resolver & resolver,
                unsigned int timeout,
                boost::asio::streambuf & request
             );

    /// @brief Shutdown connection
    void shutdown(boost::system::error_code);

    /// @brie Stop timeout timer
    void stop_timeout();

    /// @return If socket is connected
    bool is_connected() const;

private:
    friend asio_handler<http_socket,asio_http>;

    // resolve endpoint/hostname
    void resolve(
                   boost::system::error_code  err,
                   boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                );

    // begin connection
	void connect(
                   const boost::system::error_code err,
                   boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                );

    // check if we have timed out
    void time_check(const boost::system::error_code & ec);

    // members
    std::function<void(boost::system::error_code)> error_;
    std::function<void(std::string)> callback_;
    std::shared_ptr<http_socket> socket_;
    boost::asio::streambuf & request_;
    std::shared_ptr<boost::asio::deadline_timer> deadline_;
    std::atomic<bool> connected_ = { false };
};
}
}
#endif
