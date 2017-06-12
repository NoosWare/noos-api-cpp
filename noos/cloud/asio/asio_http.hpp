#ifndef NOOS_CLOUD_ASIO_HTTP
#define NOOS_CLOUD_ASIO_HTTP
/**
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio.hpp>
#include <noos/cloud/asio/asio_handler.hpp>
namespace noos {
namespace cloud {
/**
 * @class asio_http
 * @brief ASIO socket controller asynchronous http websockets used for cloud service calls
 * @version 0.7.2
 * @date 15 December 2016
 * @author Alex Giokas  <a.gkiokas@ortelio.co.uk>
 * @see asio_handler
 * @see request
 * @see response
 */
class asio_http 
: public asio_handler<http_socket>
{
public:
    /**
 	 * @brief constructor
	 * @brief `cloud_function` is the virtual `json_parser::deserialize` receiving the data
	 * @brief `error_function` is the handler which may receive the errors
	 * @brief `io_service` is the ASIO service controller
	 * @brief `request` is a stream buffer containing the request
	 */
    asio_http(
                std::function<void(std::string)> cloud_function,
                std::function<void(error_code error)> error_function,
                boost::asio::io_service & io_service,
                boost::asio::streambuf & request
             );

	/**
	 * \brief begin connection
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
     * \warning disable ssl v2 and ssl v3 (allow only tls)
	 */
	void begin(
			    boost::asio::ip::tcp::resolver::query & query,
			    boost::asio::ip::tcp::resolver & resolver,
                unsigned int timeout
              );

    /// \brief shutdown connection
    void shutdown(const boost::system::error_code);

private:

    /// \brief resolve
    void resolve(
                   boost::system::error_code  err,
                   boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                );

    /// \brief begin connection
	void connect(
                   const boost::system::error_code err,
                   boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                );

    /// \brief check if we have timed out
    void time_check();

private:
    /// error callback
    std::function<void(boost::system::error_code)> error_cb_;
    /// boost asio socket 
    std::shared_ptr<http_socket> socket_;
    /// request object
    boost::asio::streambuf & request_;
    /// deadline timer for timeouts
    std::shared_ptr<boost::asio::deadline_timer> deadline_;
};
}
}
#endif
