#ifndef NOOS_CLOUD_CALLABLE
#define NOOS_CLOUD_CALLABLE
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/cloud/asio/platform.hpp>
#include <noos/cloud/default_error_handler.hpp>
#include <noos/cloud/asio/asio_https.hpp>
#include <noos/cloud/asio/asio_http.hpp>
#include <noos/cloud/asio/platform.hpp>
#include <noos/cloud/cloud_base.hpp>
#include <noos/cloud/deserialize.hpp>
#include <noos/cloud/vision_batch.hpp>

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
          bool  keep_alive   = true,
          class socket_type  = asio_https,
          class error_handle = default_error_handler>
class callable
{
public:
    using callback = typename cloud_type::callback;
    using cloud_class = cloud_type;

    /// the actual `cloud_type` object
    /// you may change this between calls
    cloud_type object;

    /// @brief no empty constructor allowed
    callable() = delete;
    
    /// @warning you cannot copy a callable
    callable(callable const &) = delete;

	/// @warning you cannot assign a callable
    callable & operator=(const callable &) = delete;
    
    /// @warning move assignment
    callable & operator=(callable &&) = delete;

    /// @brief construct a callable using a noos::cloud::platform object
    callable(callback functor,
             platform = default_node);

    /**
     * @brief construct a callable object wrapper
     * @param `args` are the `cloud_type` constructor arguments
     * @param `functor` is the callback receiving the reply
     * @see `cloud_type::callback` for callback signature
     */
    template <typename... parameters,
              typename = typename std::enable_if<!std::is_same<cloud_type,cloud_batch>::value,bool>>
    callable(callback functor,
             platform info,
             parameters... args);

    /// @brief overloaded constructor for `vision_batch` template `cloud_type`
    /// @warning a `vision_batch` does not require a callback!
    template <typename... parameters>
    callable(vision_batch<parameters...> arg,
             platform = default_node);

    /// @brief convenience constructor for `vision_batch` classes will construct the object internally
    template <typename... parameters,
              typename = typename std::enable_if<std::is_same<cloud_type,cloud_batch>::value,bool>>
    callable(const noos::object::picture & image,
             platform info,
             parameters... args);

    /// @brief send the cloud_type data once to the cloud endpoint
    /// @note the default 2 second timeout value should suffice
    void send(unsigned int timeout = 2);
    /// @brief stop calls and shutdown socket
    void stop();
protected:
    /// @brief set the parameter socket - used by `noos::cloud::node`
    void socket(std::function<void(std::string)> cloud_function);
    /// @brief the callback functor - hidden from others
    callback functor;
    platform endpoint;
    std::unique_ptr<socket_type> socket_;
    std::unique_ptr<boost::asio::streambuf> buffer_;
    std::unique_ptr<boost::asio::ip::tcp::resolver::query> query_;
    std::unique_ptr<boost::asio::io_service> io_;
    std::unique_ptr<boost::asio::ip::tcp::resolver> resol_;
};

template <class cloud_type,
          bool  keep_alive   = true,
          class socket_type  = asio_https,
          class error_handle = default_error_handler,
          class ...args,
          typename = 
                typename std::enable_if<!std::is_same<cloud_type, 
                                                      cloud_batch>::value, bool>>
callable<cloud_type,keep_alive,socket_type,error_handle> 
    call(typename cloud_type::callback functor,
         args... params)
{
    return callable<cloud_type,
                    keep_alive,
                    socket_type,
                    error_handle>(functor, default_node, params...);
}

#include "callable.tpl"
}
}
#endif
