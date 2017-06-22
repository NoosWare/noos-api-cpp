#include "asio_http.hpp"
namespace noos {
namespace cloud {

asio_http::asio_http(
						std::function<void(std::string)> cloud_callback,
						std::function<void(error_code)> error_callback,
						boost::asio::io_service & io_service,
                        const bool keep_alive
					)
: asio_handler<http_socket>(keep_alive, error_callback),
  error_(error_callback),
  callback_(cloud_callback)
{
    socket_ = std::make_shared<http_socket>(io_service);
    deadline_ = std::make_shared<boost::asio::deadline_timer>(io_service);
	assert(callback_ && error_ && socket_ && deadline_);
    asio_handler::set_socket(socket_);
}

void asio_http::begin( 
						boost::asio::ip::tcp::resolver::query & query,
						boost::asio::ip::tcp::resolver & resolver,
						boost::asio::streambuf & request,
                        unsigned int timeout
					 )
{
    // PROBLEM: the async_wait callback will be bound to *this* 
    //          so even when the class has finished, we still have a queued
    //          operation in the io_service waiting for time_check
    deadline_->async_wait(boost::bind(&asio_http::time_check, this)); 
    deadline_->expires_from_now(boost::posix_time::seconds(timeout));
    request_(request);
    resolver.async_resolve(query,
                            boost::bind(&asio_http::resolve,
                                        this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::iterator));
}

void asio_http::resolve(
                           boost::system::error_code  err,
                           boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                       )
{
    if (!err) {
        auto endpoint = * endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_http::connect, 
                                           this, 
                                           boost::asio::placeholders::error,
                                           ++endpoint_iterator));
    }
    else {
        error_(err);
        shutdown(err);
    }
}

void asio_http::connect(
                         const boost::system::error_code err,
                         boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                       )
{
	if (!err) {
        connected_ = true;
        // write the request to the socket
        boost::asio::async_write(*socket_.get(),
                                 request_,
                                 boost::bind(&asio_handler<http_socket>::write_request, 
                                             this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));

    }
    else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
        socket_->close();
        auto endpoint = *endpoint_iterator;
        socket_->async_connect(endpoint,
                               boost::bind(&asio_http::connect, 
                                           this, 
                                           boost::asio::placeholders::error,
                                           ++endpoint_iterator));
    }
    else {
        error_(err); 
        shutdown(err);
    }
}

void asio_http::send(
                        boost::asio::ip::tcp::resolver::query & query,
                        boost::asio::ip::tcp::resolver & resolver,
                        unsigned int timeout,
                        boost::asio::streambuf & request
                    )
{
    if (connected_) {
        deadline_->expires_from_now(boost::posix_time::seconds(timeout));
        boost::asio::async_write(*socket_.get(),
                                 request_,
                                 boost::bind(&asio_handler<http_socket>::write_request, 
                                             this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
    else {
        auto error = boost::asio::error::eof
        shutdown(error);
    }
}

void asio_http::shutdown(const boost::system::error_code err)
{
    connected_ = false;
    socket_->close();
    deadline_->cancel();
    deadline_.reset(); 
}

void asio_http::stop_timeout()
{
    deadline_->cancel();
}

void asio_http::time_check()
{
    // BUG: this is a bad way of handling deadline expiration
    // deadline pointer has expired?!
    if (!deadline_) {
        return;
    }
    if (deadline_->expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
        #if (!NDEBUG)
        std::cerr << "[time-out]: closing socket" << std::endl;
        #endif
        socket_->close();
        deadline_->cancel();
        connected_ = false;
    }
    else {
        deadline_->async_wait(boost::bind(&asio_http::time_check, this));
    }
}

}
}
