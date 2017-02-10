#include "service_controller.hpp"

namespace rapp {
namespace cloud {

service_controller::service_controller(rapp::cloud::platform info)
: info_(info), 
  query_(info.address, info.port), 
  io_(), 
  resol_(io_),
  timeout_(1)
{
    // TODO: test the info params?
    derr_cb_ = std::bind(&service_controller::default_error_handler, 
                         this, 
                         std::placeholders::_1);
}

service_controller::service_controller(
                                        rapp::cloud::platform info,
                                        std::function<void(boost::system::error_code error)> error_handler
                                      )
: info_(info), 
  query_(info.address, info.port), 
  io_(), 
  resol_(io_), 
  error_(error_handler),
  timeout_(1)
{}

void service_controller::set_timeout(unsigned long int timeout)
{
    timeout_ = timeout;
}

void service_controller::stop()
{
    io_.stop();
}

void service_controller::default_error_handler(boost::system::error_code error) const
{
#if (!NDEBUG)
    std::cerr << "[error-message]: " << error.message() 
              << " [error-value]: " << error.value() << std::endl;
#endif
}

void service_controller::batch_call(vision_batch & batch)
{
    batch.end(); 

    boost::asio::streambuf request;
    for (auto obj : batch.get_services()) {
        obj->fill_buffer(boost::ref(request), info_);
        std::function<void(std::string)> callback = [&](auto reply) {
            obj->deserialise(reply);
        };
    }
    //// create an asio_socket and run the request
    //auto asio = std::make_unique<asio_http>(callback, derr_cb_, io_, request); 
    //assert(asio);
    //// start
    //asio->begin(query_, resol_, timeout_);
    //io_.run();
    //io_.reset();

}

}
}
