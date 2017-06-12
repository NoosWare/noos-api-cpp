#ifndef CLOUD_NODE
#define CLOUD_NODE
/**
 * LICENSE HERE
 */
#include "includes.ihh"
#include <rapp/cloud/asio/platform.hpp>
#include <rapp/cloud/default_error_handler.hpp>
namespace rapp {
namespace cloud {
/**
 * @class node
 * @brief node which handles cloud calls
 * @version 0.7.3
 * @date 7 June 2017
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * @note template parameter `socket_type` and defaults to `asio_http`
 * @note template parameter `error_handle` is the callback which receives the errors,
 *       and it defaults to `default_error_handler`
 *
 * TODO (0.7.3): enable choice of HTTP or TLS
 *				 enable choice of TLS CA.PEM file (pass to asio_https)
 *               enable choice of ignoring CA on TLS
 */
template <class socket_type = rapp::cloud::asio_http,
          class error_handle = rapp::cloud::default_error_handler>
class node
{
public:
    /// @brief for convenience
    using socket_class = socket_type;

    /** 
     * @brief construct a service controller using a rapp::cloud::platform object
     * @param info must contain all required fields
     */
	node(rapp::cloud::platform);

    /// @brief set a time-out different than the default of 1 second
    void set_timeout(unsigned long int);

    /**
     * @brief construct a cloud callable object
     * @note template parameter `cloud_type` is the cloud class
     * @note template parameter `callback` is the user-defined callback receiving the reply
     * @return a `callable` object of same template parameter types
     * @see  `cloud_type::callback` for the correct callback signature
     * @see  `rapp::cloud::callable` for the return type
     */
    template <class cloud_type,
              class callback>
    callable<cloud_type,callback,socket_type> make_one(cloud_type, callback);

    /**
     * @brief same as `make_one` only this one constructs the `cloud_type` object using variadic args
     * @note template parameter `cloud_type` is the cloud class
     * @note template parameter `callback` is the user-defined callback receiving the reply
     * @return a `callable` object of same template parameter types
     * @see  `cloud_type::callback` for the correct callback signature
     * @see  `rapp::cloud::callable` for the return type
     */
    template <class cloud_type, 
              class callback,
              typename... parameters>
    callable<cloud_type,callback,socket_type> make_one(parameters..., callback);

    /// TODO: create a method `make_batch`
    ///       either via cloud_type or via variadic template

    /** 
     * @brief create batch of cloud calls using a variadic template
     * @param `args` is a variadic template of cloud classes
     * @return a tuple of various `rapp::cloud::callable` objects (same order as the @parameter `args`)
     */
    template <typename... callables> 
    std::tuple<callables...> make_many(callables... );
    
    /**
     * @brief call a cloud service once
     * @param arg assumes a properly constructed callable with a socket assigned
     * @throws exception if socket is not set
     */
    template <class cloud_type,
              class callback>
    void call_one(callable<cloud_type,callback,socket_type> & arg);

    /// TODO: create a method `call_batch`

    /**
     * @brief call many cloud services in parallel
     * @warning assumes that callables are of class `callable` already constructed,
     *          and that they have properly constructed sockets
     */
    template <typename... callables>
    void call_many(callables... & args);

    /** 
     * @brief create and execute a cloud callable object
     * @note template parameter `cloud_type` is the cloud class object already constructed
     * @note template parameter `callback` is the user-defined callback receiving the reply
     * @see  `cloud_type::callback` for the correct callback signature
     */
    template <class cloud_type,
              class callback>
    callable<cloud_type,callback,socket_type> make_call_one(cloud_type obj, callback functor);

    /** 
     * @brief construct and execute a cloud callable object
     * @note template parameter `cloud_type` is a cloud class
     * @note template parameter `callback` is the user-defined callback receiving the reply
     * @note template variadic `args` is the `service_type` construction parameters
     * @see  `cloud_type::callback` for the correct callback signature
     */
    template <class cloud_type, 
              class callback,
              typename... parameters>
    callable<cloud_type,callback,socket_type> make_call_one(parameters... args, callback functor);

    /// @brief stop the service controller
    void stop();
 
private:
	// cloud params
    rapp::cloud::platform info_;
    // resolution, query and io service
    boost::asio::ip::tcp::resolver::query query_;
	// service IO for TCP/IP control
    boost::asio::io_service io_;
	// address resolver
    boost::asio::ip::tcp::resolver resol_;
    // default timeout
    unsigned long int timeout_;
};
#include "node.tpl"
}
}
#endif
