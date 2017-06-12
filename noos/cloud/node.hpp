#ifndef NOOS_CLOUD_NODE
#define NOOS_CLOUD_NODE
/**
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/cloud/callable.hpp>
#include <noos/cloud/default_error_handler.hpp>
#include <noos/cloud/asio/asio_http.hpp>
#include <noos/cloud/asio/platform.hpp>
#include <noos/cloud/cloud_batch.hpp>
#include <noos/cloud/deserialize.hpp>
#include <noos/cloud/vision_batch.hpp>
namespace noos {
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
 * @note wherever a template parameter `cloud_type` is used, assume it is a cloud class.
 * @note when using a template parameter `callback` check the class's `callback` for the correct signature.
 * @warningi when using a variadic argument list, only non-batched classes can be used!
 *
 * TODO (0.7.3): enable choice of HTTP or TLS
 *				 enable choice of TLS CA.PEM file (pass to asio_https)
 *               enable choice of ignoring CA on TLS
 */
template <class socket_type = noos::cloud::asio_http,
          class error_handle = noos::cloud::default_error_handler>
class node
{
public:
    /// @brief for convenience
    using socket_class = socket_type;

    /** 
     * @brief construct a service controller using a noos::cloud::platform object
     * @param info must contain all required fields
     */
	node(noos::cloud::platform);

    /// @brief set a time-out different than the default of 1 second
    void set_timeout(unsigned long int);

    /// @brief stop the service controller, this will drop all active connections
    void stop();

    /**
     * @brief construct a cloud callable object
     * @return a `callable` object of same template parameter types
     */
    template <class cloud_type,
              class callback>
    callable<cloud_type,callback,socket_type> make(cloud_type, callback);

    /**
     * @brief same as `make_one` only this one constructs the `cloud_type` object using variadic args
     * @return a `callable` object of same template parameter types
     */
    template <class cloud_type, 
              class callback,
              class... parameters>
    callable<cloud_type,callback,socket_type> make(parameters..., callback);

    /**       
     * @brief a template specialisation of `make` for `vision_batch` only
     * @note variadic template `cloud_pairs` are `std::pair` of `cloud_type` and `callback`
     * @see `noos::cloud::vision_batch` for more information
     * @return a callable which wraps around a `vision_batch` object
     */
    template <class... cloud_pairs>
    callable<vision_batch<cloud_pairs...>,
             typename vision_batch<cloud_pairs...>::callback,
             socket_type> make(cloud_pairs ...);

    /** 
     * @brief create batch of cloud calls using a variadic template
     * @param `args` is a variadic template of cloud classes
     * @return a tuple of various `noos::cloud::callable` objects (same order as the @parameter `args`)
     */
    template <class... callables> 
    std::tuple<callables...> pack(callables ...);
    
    /**
     * @brief call a cloud service once
     * @param arg assumes a properly constructed callable with a socket assigned
     * @throws exception if socket is not set
     */
    template <class cloud_type,
              class callback>
    void call(callable<cloud_type, callback, socket_type> &);
    
    /**
     * @brief call many cloud services in parallel
     * @warning assumes that callables are of class `callable` already constructed,
     *          and that they have properly constructed sockets
     */
    template <class... callables>
    void call(callables & ...args);

    /** 
     * @brief call multiple cloud services in parallel
     * @note you must have created a callable tuple using `pack`
     * @note variadic `callables` is a list of various callable wrappers
     */
    template <class... callables>
    void call(std::tuple<callables...> &);

    /// @brief create and execute a cloud callable object - used for convenience mostly
    template <class cloud_type,
              class callback>
    callable<cloud_type,callback,socket_type> make_call(cloud_type obj, callback functor);

    /** 
     * @brief construct and execute a cloud callable object - used for convenience mostly
     * @note template variadic `parameters` are the `cloud_type` construction parameters
     */
    template <class cloud_type, 
              class callback,
              class... parameters>
    callable<cloud_type,callback,socket_type> make_call(parameters... args, callback functor);

    /**
     * @brief pack a list of callable cloud services and call them - used for convenience mostly
     * @return a tuple of callables
     */
    template <class... callables>
    std::tuple<callables...> pack_call(callables ...);
     
private:
    void run_reset();

    error_handle error_;
    noos::cloud::platform info_;
    boost::asio::ip::tcp::resolver::query query_;
    boost::asio::io_service io_;
    boost::asio::ip::tcp::resolver resol_;
    unsigned long int timeout_;
};
#include "node.tpl"
}
}
#endif
