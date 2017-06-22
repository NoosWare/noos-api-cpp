#ifndef NOOS_CLOUD_CALLABLE
#define NOOS_CLOUD_CALLABLE
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/cloud/asio/platform.hpp>
namespace noos {
namespace cloud {
/**
 * @class callable
 * @brief a class which wraps around a cloud call, its socket, buffer and callback
 * @version 0.7.3
 * @date 8 June 2017
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
template <class cloud_type,
          class callback,
          class socket_type>
struct callable
{
    cloud_type object;
    callback functor;
    using cloud_class = cloud_type;
    
    /**
     * @brief construct a callbable object wrapper
     * @param `functor` is the callback receiving the reply
     * @param `object` is the cloud data being sent
     * @see `cloud_type::callback` for callback signature
     */
    callable(cloud_type object, callback functor);

    /**
     * @brief construct a callable object wrapper
     * @param `args` is the variadic `cloud_type` constructor arguments
     * @param `functor` is the callback receiving the reply
     * @see `cloud_type::callback` for callback signature
     */
    template <typename... parameters>
    callable(parameters... args, callback functor);

    /// @brief set the @param socket - used by `rapp::cloud::node`
    void socket(std::function<void(std::string)> cloud_function,
                std::function<void(boost::system::error_code)> error_function,
                boost::asio::io_service & io_service,
                bool keep_alive);

    /// @brief send the cloud_type data once to the cloud endpoint
    void send(boost::asio::ip::tcp::resolver::query & query,
			  boost::asio::ip::tcp::resolver & resolver,
              unsigned int timeout,
              noos::cloud::platform endpoint);
private:
    std::unique_ptr<socket_type> socket_;
    std::unique_ptr<boost::asio::streambuf> buffer_;
};
#include "callable.tpl"
}
}
#endif
