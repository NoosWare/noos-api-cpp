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
 *
 * template parameter `socket_type` can be either `asio_http` or `asio_https` (UNTESTED)
 * template parameter `error_handle` is the callback which receives the errors,
 * and it defaults to `default_error_handler`
 *
 * TODO (0.7.3): enable choice of HTTP or TLS
 *				 enable choice of TLS CA.PEM file (pass to asio_https)
 *               enable choice of ignoring CA on TLS
 *
 *               RENAME CLASS
 *               overload methods to re-use sockets
 *               return sockets used
 *               template error handler
 *               template socket type
 *               change call methods to use a callback (which is removed from data cloud classes)
 *               GENERIC OVERHAUL
 */
template <class socket_type,
          class error_handle = default_error_handler>
class node
{
public:
    /** 
     * @brief construct a service controller using a rapp::cloud::platform object
     * @param info must contain all required fields
     */
	node(rapp::cloud::platform);

    /// @brief set a time-out different than the default of 1 second
    void set_timeout(unsigned long int);

    /** 
     * @brief construct and execute a cloud callable object
     * template parameter 'service_type' is a the cloud class object already constructed
     *
     * TODO: requires user-defined callback*
     */
    template <class service_type,
              class callback>
    void make_call(service_type obj, callback functor);

    /** 
     * @brief construct and execute a cloud callable object
     * template parameter `service_type` is a cloud class
     * template variadic `args` is the `service_type` cloud class construction arguments
     *
     * TODO: requires user-defined callback
     */
    template <class service_type, 
              class callback,
              typename... Args>
    void make_call(Args... args, callback functor);

    /** 
     * @brief create batch of cloud calls using a variadic template
     * @param `args` is a variadic template of cloud classes
     *
     * TODO: examine if this can be used, or if it must be deprecated
     */
    template <typename... Args> 
    void make_calls(Args... args);

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

/* 
 * Template Implementations
 */
template <class socket_type,
          class error_handle>
node<socket_type,error_handle>::node(rapp::cloud::platform info)
: info_(info), 
  query_(info.address, info.port), 
  io_(), 
  resol_(io_),
  timeout_(1)
{}

template <class socket_type,
          class error_handle>
void node<socket_type,error_handle>::set_timeout(unsigned long int timeout)
{
    timeout_ = timeout;
}

template <class socket_type,
          class error_handle>
void node<socket_type,error_handle>::stop()
{
    io_.stop();
}

template <class socket_type,
          class error_handle>
template <class service_type,
          class callback>
void node<socket_type,error_handle>::make_call(service_type obj, callback functor)
{
    boost::asio::streambuf request;
    obj.fill_buffer(boost::ref(request), info_);
    auto cb = [&](auto reply) { 
        functor(deserialize<service_type, obj::data_type>(reply));
    };

    // create an asio_socket and run the request
    auto asio = std::make_unique<asio_http>(cb, error_handle, io_, request); 
    assert(asio);
    asio->begin(query_, resol_, timeout_);
    io_.run();
    io_.reset();
}

template <class socket_type,
          class error_handle>
template <class service_type, 
          typename... Args>
void node<socket_type,error_handle>::make_call(Args... args)
{
    // create the cloud class
    auto obj = service_type(args...);
    boost::asio::streambuf request;
    obj.fill_buffer(boost::ref(request), info_);

    auto cb = [&](auto reply) { 
        auto result = deserialize<service_type, obj::data_type>(reply);
        // TODO: user defined callback will receive the result
    };

    // create socket, which will call deserialize to load string to json
    auto asio = std::make_unique<asio_http>(cb, error_handle, io_, request); 
    assert(asio);
    asio->begin(query_, resol_, timeout_);
    io_.run();
    io_.reset();
}

/*
template <typename... Args>
void service_controller::make_calls(Args... args)
{
    std::vector<std::pair<std::shared_ptr<boost::asio::streambuf>,
                          std::shared_ptr<asio_http>>> sockets;
    // iterate each argument (has already been constructed and is non-copyable)
    misc::for_each_arg([&](auto & obj) {
        // allocate buffer  - must live as long as socket
        auto buffer = std::make_shared<boost::asio::streambuf>();
        // fill buffer
        obj.fill_buffer(boost::ref(*buffer), info_);
        // make socket - must live as long as the io_service uses it!
        auto socket = std::make_shared<asio_http>([&](auto reply){ obj.process(reply); }, 
                                                  error_handle, io_, *buffer);
        // keep the socket and buffer alive and start the connection
        sockets.emplace_back(std::make_pair(buffer, socket));
        sockets.back().second->begin(query_, resol_, timeout_);
    }, args...);

    // run all calls, then reset asio queue
    io_.run();
    io_.reset();
}
*/

}
}
#endif
