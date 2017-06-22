#ifndef NOOS_CLOUD_ASIO_HTTPS
#define NOOS_CLOUD_ASIO_HTTPS
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <noos/cloud/asio/asio_handler.hpp>
namespace noos {
namespace cloud {
/**
 * @class asio_https
 * @brief ASIO socket controller for TLS (encrypred) cloud service calls
 * @version 0.7.2
 * @date 15 December 2016
 * @author Alex Giokas  <a.gkiokas@ortelio.co.uk>
 * @see asio_handler
 * @see request
 * @see response
 */
class asio_https 
: public asio_handler<tls_socket, asio_https>
{
public:
	/**
	 * @brief constructor
	 * @brief `cloud_function` is the virtual `json_parser::deserialize` receiving the data
	 * @brief `error_function` is the handler which may receive the errors
	 * @brief `io_service` is the ASIO service controller
	 * @brief `request` is a stream buffer containing the request
	 * @TODO (0.7.3) take as param a PEM filename to evaluate CA - currently the server CE is not evaluated!!!
	 */
    asio_https(
                std::function<void(std::string)> cloud_callback,
                std::function<void(error_code error)> error_callback,
                boost::asio::io_service & io_service,
                boost::asio::streambuf & request,
                bool keep_alive
             );

	/**
	 * \brief begin connection
	 * \param query defines the URL/URI
	 * \param resolver resolves the URL/URI address
     * \param io_service is the queue on which jobs are scheduled
     * \warning only TLS 1.2 and later are allowed
	 */
	void begin(
			    boost::asio::ip::tcp::resolver::query & query,
			    boost::asio::ip::tcp::resolver & resolver,
                unsigned int timeout
              );

    /// \brief shutdown handler
    void shutdown(const boost::system::error_code);

    /// @brie stop timeout timer
    void stop_timeout();

private:
    friend asio_handler<tls_socket,asio_https>;

	/// \brief verify TLS certificate
	bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

	/// \brief begin connection
	void connect(const boost::system::error_code err);

	/// \brief handle handshake
  	void handshake(const boost::system::error_code err);
    
    /// \brief check if we have timed out
    void time_check();

    std::function<void(boost::system::error_code err)> error_;
    std::function<void(std::string)> callback_;
	boost::asio::ssl::context ctx_;
    std::shared_ptr<tls_socket> socket_;
    boost::asio::streambuf & request_;
    std::shared_ptr<boost::asio::deadline_timer> deadline_;
};
}
}
#endif
