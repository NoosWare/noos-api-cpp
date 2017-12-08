#ifndef NOOS_ASIO_HANDLER
#define NOOS_ASIO_HANDLER
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <boost/asio/ssl.hpp>
#include <noos/cloud/asio/http_response.hpp>
typedef boost::asio::ip::tcp::socket http_socket;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> tls_socket;
typedef boost::system::error_code error_code;
typedef boost::asio::ip::tcp::resolver resolver;

namespace noos {
/// @brief common cloud namespace
namespace cloud {
/**
 * @class asio_handler
 * @version 0.7.0
 * @date 12 August 2016 
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @brief ASIO socket controller of boost asio socket type T
 * @note This class is used internally from `asio_http` and `asio_https`.
 */
template <class socket_type,
          class child_class> 
class asio_handler 
: protected http_response
{
public:
    /**
     * @brief construct by callbacks and socket T pointer 
     * @param cloud_function will receive the platform JSON reply
     * @param error_function will receive any asio errors
     * @param socket is the actual type T socket pointer
     */
    asio_handler(const bool keep_alive,
                 std::function<void(error_code)> error_callback);

    /// @brief set socket pointer
    void set_socket(const std::shared_ptr<socket_type> socket);
	    
    /** 
     * @brief write the cloud request to the socket
     * @param err is propagated from boost asio
     */
    void write_request(const boost::system::error_code & err,
                       const std::size_t bytes);

    /** 
     * @brief read first HTTP line and check for a 200 response
     * @param err is propagated from boost asio
     */
    void read_status_line(const boost::system::error_code & err,
                          const std::size_t bytes);
    
    /** 
     * @brief read HTTP headers and validate
     * @param err is propagated from boost asio
     */
    void read_headers(const boost::system::error_code & err,
                      const std::size_t bytes);

    /** 
     * @brief strip the header and read the POST data
     * @param err is propagated from boost asio
     */
    void read_content(
                      const boost::system::error_code & err,
                      const std::size_t bytes
                     );

    /**
     * @brief close socket and cleanup members
     * @param err is propagated from boost asio
     */
    void end(const boost::system::error_code & err);

protected:
    std::shared_ptr<socket_type> socket_;
    bool keep_alive_ = false;
};
}
}
#include "asio_handler.tpl"
#endif
