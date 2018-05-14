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
/// @brief Common cloud namespace
namespace cloud {
/**
 * @class asio_https
 * @brief ASIO socket controller for TLS (encrypred) cloud service calls
 * @version 0.7.2
 * @date 15 December 2016
 * @author Alex Giokas  <a.gkiokas@ortelio.co.uk>
 * @see asio_handler
 * @see http_request
 * @see http_response
 */
class asio_https 
: public asio_handler<tls_socket, asio_https>
{
public:
	/**
	 * @brief Constructor
	 * @param cloud_function is the virtual `json_parser::deserialize` receiving the data
	 * @param error_function is the handler which may receive the errors
	 * @param io_service is the ASIO service controller
	 * @param request is a stream buffer containing the request
	 */
    asio_https(
                std::function<void(std::string)> cloud_callback,
                std::function<void(error_code error)> error_callback,
                boost::asio::io_service & io_service,
                const bool keep_alive,
                boost::asio::streambuf & request
             );

    /**
     * @brief Begin connection
     * @param query defines the URL/URI
     * @param resolver resolves the URL/URI address
     * @param io_service is the queue on which jobs are scheduled
     * @warning only TLS 1.2 and later are allowed
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

    /// @brief Shutdown handler
    void shutdown(const boost::system::error_code);

    /// @brief Stop timeout timer
    void stop_timeout();

    /// @return If socket is connected
    bool is_connected() const;

private:
    friend asio_handler<tls_socket,asio_https>;

    // \brief verify TLS certificate
    bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx);

    // \brief begin connection
    void connect(const boost::system::error_code err);

    // \brief handle handshake
    void handshake(const boost::system::error_code err);

    // \brief check if we have timed out
    void time_check(const boost::system::error_code & ec);

    // \brief convert ASN1_INTEGER to std::string
    std::string asn1_to_string(ASN1_INTEGER * serial);

    std::function<void(boost::system::error_code err)> error_;
    std::function<void(std::string)> callback_;
    boost::asio::ssl::context ctx_;
    std::shared_ptr<tls_socket> socket_;
    boost::asio::streambuf & request_;
    std::shared_ptr<boost::asio::deadline_timer> deadline_;
    std::atomic<bool> connected_ = { false };
    static const std::string serial_certificate__;
    static const std::string serial_certificate2__;
    static const std::string serial_certificate3__;
    static const char hexbytes_[];
};
}
}
#endif
