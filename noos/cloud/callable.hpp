#ifndef NOOS_CLOUD_CALLABLE
#define NOOS_CLOUD_CALLABLE
/**
 * LICENSE HERE
 */
#include "includes.ihh"
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
    void set_socket(std::unique_ptr<socket_type> socket);

    /// @return socket reference
    socket_type & get_socket() const;

    /// @return buffer reference
    boost::asio::streambuf & get_buffer() const;

private:
    std::unique_ptr<socket_type> socket_;
    std::unique_ptr<boost::asio::streambuf> buffer_;
};
#include "callable.tpl"
}
}
#endif
