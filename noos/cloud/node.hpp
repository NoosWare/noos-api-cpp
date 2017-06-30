#ifndef NOOS_CLOUD_NODE
#define NOOS_CLOUD_NODE
/*
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
#include <noos/cloud/goodbye.hpp>
/// @brief noos API namespace
namespace noos {
/// @brief cloud service namespace
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
 * @note wherever a template parameter `cloud_type` is used, it must be an existing cloud class.
 * @note when using a template parameter `callback` check the class's alias `callback` for the correct function signature.
 *
 * @todo (0.7.3): implement partial specialisations for `asio_https` (TLS certificate)
 *				  TLS CA.PEM file (pass to asio_https)
 *                choice of ignoring CA on TLS (bad option!)
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

    /** 
     * @brief construct a service controller using a nlohmann::json object
     * @param json must contain all required fields of noos::cloud::platform object
     */    
    node(json);

    /** 
     * @brief construct a service controller using a ini file
     * @param filename must contain a JSON with all required
     *        fields of noos::cloud::platform object
     */
    node(std::string filename);

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
    callable<cloud_type,
             callback,
             socket_type,
             error_handle> make(cloud_type, callback);

    /**
     * @brief same as `make_one` only this one constructs the `cloud_type` object using variadic args
     * @return a `callable` object of same template parameter types
     * \test Alex Giokas
     */
    template <class cloud_type, 
              class callback,
              class... parameters>
    callable<cloud_type,
             callback,
             socket_type,
             error_handle> make(parameters..., callback);

    /**       
     * @brief a template specialisation of `make` for `vision_batch` only
     * @note variadic template `cloud_pairs` are `std::pair` of `cloud_type` and `callback`
     * @see `noos::cloud::vision_batch` for more information
     * @return a callable which wraps around a `vision_batch` object
     */
    template <class... cloud_pairs>
    callable<vision_batch<cloud_pairs...>,
             typename vision_batch<cloud_pairs...>::callback,
             socket_type,
             error_handle> make(const noos::object::picture &, cloud_pairs...);

    /** 
     * @brief create batch of cloud calls using a variadic template
     * @param `args` is a variadic template of cloud classes
     * @return a tuple of various `noos::cloud::callable` objects (same order as the @parameter `args`)
     * \test Alex Giokas
     */
    template <class... callables> 
    std::tuple<callables...> pack(callables ...);

    /**
     * @brief call once a noos service and then close the connection
     * @param object of `cloud_type` can be any kind of cloud class
     * @param functor is the callback that will receive the reply
     * @note you don't need to invoke `make` for this type of call
     */
    template <class cloud_type,
              class callback>
    void call_once(cloud_type object, callback functor);

    /**
     * @brief call once a noos service and then close the connection
     * @param args (varadic arguments) are the ones used to construct the `cloud_type` object
     * @param functor is the callback that will receive the reply
     * @note you don't need to invoke `make` for this type of call
     */
    template <class cloud_type,
              class... parameters,
              class callback>
    void call_once(parameters... args, callback functor);
    
    /**
     * @brief call a cloud service once
     * @param arg assumes a properly constructed callable using `make`
     * @throws exception if socket is not set
     */
    template <class cloud_type,
              class callback>
    void call(callable<cloud_type,callback,socket_type,error_handle> & arg);
    
    /**
     * @brief call many cloud services in parallel
     * @warning assumes that callables are of class `callable` already constructed,
     *          and that they have properly constructed sockets
     * \test Alex Giokas
     */
    template <class... callables>
    void call(callables & ...args);

    /** 
     * @brief call multiple cloud services in parallel
     * @note you must have created a callable tuple using `pack`
     * @note variadic `callables` is a list of various callable wrappers
     * \test Alex Giokas
     */
    template <class... callables>
    void call(std::tuple<callables...> &);

    /// @brief create and execute a cloud callable object - used for convenience mostly
    template <class cloud_type,
              class callback>
    callable<cloud_type,
             callback,
             socket_type,
             error_handle> make_call(cloud_type obj, callback functor);

    /** 
     * @brief construct and execute a cloud callable object - used for convenience mostly
     * @note template variadic `parameters` are the `cloud_type` construction parameters
     * \test Alex Giokas
     */
    template <class cloud_type, 
              class callback,
              class... parameters>
    callable<cloud_type,
             callback,
             socket_type,
             error_handle> make_call(parameters... args, callback functor);

    /**
     * @brief pack a list of callable cloud services and call them - used for convenience mostly
     * @return a tuple of callables, which have been called together in a batch
     * \test Alex Giokas
     */
    template <class... callables>
    std::tuple<callables...> pack_call(callables ...);

protected:
    void run_reset();

private:
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
