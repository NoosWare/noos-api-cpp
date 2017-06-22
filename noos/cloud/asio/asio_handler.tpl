namespace noos {
namespace cloud {

template <class socket_type,
          class child_class> 
asio_handler<T>::asio_handler(const bool keep_alive,
                              std::function<void(error_code)> error_callback)
: http_response(error_callback), 
  keep_alive_(keep_alive)
{}

template <class socket_type,
          class child_class> 
void asio_handler<T>::set_socket(const std::shared_ptr<T> socket)
{
    assert(socket);
    socket_ = socket;
}

template <class socket_type,
          class child_class> 
void asio_handler<T>::write_request(const boost::system::error_code & err,
                                    const std::size_t bytes)
{
    if (err){ 
        end(err);
        return;
    }
    boost::asio::async_read_until(*socket_,
                                  buffer_,
                                  "\r\n",
                                  boost::bind(&asio_handler::read_status_line, 
                                              this, 
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
}

template <class socket_type,
          class child_class> 
void asio_handler<T>::read_status_line(const boost::system::error_code & err,
                                       const std::size_t bytes)
{
    if (!err) {
       if (http_response::check_http_header()) {
        // read entire header (double newlines denote end of HTTP header) - callback `read_headers`
        boost::asio::async_read_until(*socket_,
                                      buffer_, 
                                      "\r\n\r\n",
                                      boost::bind(&asio_handler::read_headers, 
                                                  this, 
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred));
        }
    }
    else {
        end(err);
	}
}

template <class socket_type,
          class child_class> 
void asio_handler<T>::read_headers(const boost::system::error_code & err,
                                   const std::size_t bytes)
{
    if (!err) {
        // strip HTTP Header, calculate actual POST bytes received,
        // and if needed ask for more POST data.
        unsigned int remaining = http_response::strip_http_header(bytes);
        if (remaining > 0) {
            boost::asio::async_read(*socket_.get(),
                                    buffer_,
                                    boost::asio::transfer_at_least(remaining),
                                    boost::bind(&asio_handler::read_content, 
                                                this, 
                                                boost::asio::placeholders::error, 
                                                boost::asio::placeholders::bytes_transferred));
        }
        // we may have received all the data at once
        // in which case simply close and quit 
        // we add zero bytes, since we called `strip_http_header`
        // We have consumed ALL data, read the buffer and are closing the connection
        else {
            http_response::consume_buffer(static_cast<child_class*>(this)->callback_, bytes);
            if (!keep_alive_) {
                static_cast<child_class*>(this)->shutdown(
                    boost::system::errc::make_error_code(boost::system::errc::success));
            }
            else {
                static_cast<child_class*>(this)->stop_timeout();
                http_response::flush_data();
            }
        }
    }
    else {
        end(err);
	}
}

template <class socket_type>
void asio_handler<T>::read_content(
                                    const boost::system::error_code & err,
                                    const std::size_t bytes
                                  )
{
    if (!err) {
        // received all data 
        if (http_response::consume_buffer(cloud_cb_, bytes)) {
            if (!keep_alive_) {
                static_cast<child_class*>(this)->shutdown(
                    boost::system::errc::make_error_code(boost::system::errc::success));
            }
            else {
                static_cast<child_class*>(this)->stop_timeout();
                http_response::flush_data();
            }
        }
        // still data left to receive
        else {
            unsigned int left = http_response::content_length() - http_response::bytes_received();
            boost::asio::async_read(*socket_.get(),
                                    http_response::buffer_,
                                    boost::asio::transfer_at_least(left),
                                    boost::bind(&asio_handler::read_content, 
                                                this, 
                                                boost::asio::placeholders::error, 
                                                boost::asio::placeholders::bytes_transferred));
        }
    }
    // error - handle it now
    else {
        end(err);
	}
}

template <class socket_type>
void asio_handler<T>::end(const boost::system::error_code & err)
{
    if (err) {
        static_cast<child_class*>(this)->error_(err);
    }
    http_response::flush_data();
    static_cast<child_class*>(this)->shutdown(err);
}

}
}
