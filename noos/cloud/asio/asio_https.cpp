#include "asio_https.hpp"
namespace noos {
namespace cloud {

const std::string asio_https::name_certificate__ = "/CN=*.noos.cloud";
asio_https::asio_https(
                        std::function<void(std::string)> cloud_callback,
                        std::function<void(error_code error)> error_callback,
                        boost::asio::io_service & io_service,
                        const bool keep_alive,
						boost::asio::streambuf & request
					  )
:  asio_handler<tls_socket,asio_https>(keep_alive, error_callback),
   error_(error_callback), 
   callback_(cloud_callback),
   ctx_(boost::asio::ssl::context::tlsv12_client),
   request_(request)
{
    socket_ = std::make_shared<tls_socket>(io_service, ctx_);
    deadline_ = std::make_shared<boost::asio::deadline_timer>(io_service);
    assert(callback_ && error_ && socket_);
    asio_handler::set_socket(socket_);
    deadline_->async_wait(boost::bind(&asio_https::time_check, this, _1)); 
    // set context option for TLS - allow only TLS v1.2 and later
    ctx_.set_options(boost::asio::ssl::context::default_workarounds
                    | boost::asio::ssl::context::no_sslv2
                    | boost::asio::ssl::context::no_sslv3
                    | boost::asio::ssl::context::no_tlsv1
                    | boost::asio::ssl::context::no_tlsv1_1
                    | boost::asio::ssl::context::single_dh_use);
}

void asio_https::begin(
                        boost::asio::ip::tcp::resolver::query & query,
                        boost::asio::ip::tcp::resolver & resolver,
                        unsigned int timeout
					  )
{
	// if using a self-signed certificate the only way to pass verification
	// is to "install" it locally and use it for comparison
	socket_->set_verify_mode(boost::asio::ssl::verify_peer);
	socket_->set_verify_callback(boost::bind(&asio_https::verify_certificate, 
                                             this, _1, _2));
	// resolve and connect
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    boost::system::error_code error = boost::asio::error::host_not_found;

	if (endpoint_iterator != end) {
        deadline_->expires_from_now(boost::posix_time::seconds(timeout));
		boost::asio::async_connect(socket_->lowest_layer(), 
								   endpoint_iterator,
								   boost::bind(&asio_https::connect, 
                                               this, 
                                               boost::asio::placeholders::error));
	}
    else {
        asio_handler::end(error);
	}
}

bool asio_https::verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
{
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    if (strcmp(name_certificate__.c_str(), subject_name) == 0)
        return true;
    return false;
}

void asio_https::connect(const boost::system::error_code err)
{
    if (err) {
        asio_handler::end(err);
        return;
    }
	connected_ = true;
    socket_->async_handshake(boost::asio::ssl::stream_base::client,
                             boost::bind(&asio_https::handshake, 
                                         this, 
                                         boost::asio::placeholders::error));
}

void asio_https::handshake(const boost::system::error_code err)
{
    if (err) {
        asio_handler::end(err);
#if(DEBUG)
        std::cerr << "[Handshake failed]: " << err.message() << "\n";
#endif
        return;
    }
	boost::asio::async_write(*socket_,
							 request_,
							 boost::bind(&asio_handler::write_request, 
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void asio_https::send(boost::asio::ip::tcp::resolver::query & query,
                      boost::asio::ip::tcp::resolver & resolver,
                      unsigned int timeout,
                      boost::asio::streambuf & request)
{
    if (connected_) {
        deadline_->expires_from_now(boost::posix_time::seconds(timeout));
        deadline_->async_wait(boost::bind(&asio_https::time_check, this, _1)); 
        boost::asio::async_write(*socket_.get(),
                                 request,
                                 boost::bind(&asio_handler::write_request, 
                                             this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
    else {
        auto err = boost::asio::error::eof;
        shutdown(err);
    }
}

void asio_https::shutdown(const boost::system::error_code err)
{
    connected_ = false;
    socket_->lowest_layer().close();
	if (deadline_) { 
		deadline_->cancel();
		deadline_.reset();
	}
    if (err.value() != 0) 
        error_(err); 
}

void asio_https::stop_timeout()
{
    assert(deadline_);
    deadline_->cancel();
}

void asio_https::time_check(const boost::system::error_code & ec)
{
    if (!deadline_) {
        return;
    }
    if (ec != boost::asio::error::operation_aborted) { 
        #if (!NDEBUG)
        std::cerr << "[time-out]: closing socket" << std::endl;
        #endif
        error_(boost::asio::error::timed_out);
        shutdown(boost::asio::error::timed_out);
    }
    else {
        return;
    }

}

bool asio_https::is_connected() const
{
    return connected_;
}

}
}
