/*
 * Template implementation
 */
template <class cloud_type,
          class callback,
          class socket_type>
callable<cloud_type,callback,socket_type>::callable(cloud_type object,
                                                    callback functor)
: object(object), 
  functor(functor), 
  buffer_(std::make_unique<boost::asio::streambuf>())
{ }

template <class cloud_type,
          class callback,
          class socket_type>
template <typename... parameters>
callable<cloud_type,callback,socket_type>::callable(parameters... args,
                                                    callback functor)
: object(args...), 
  functor(functor),
  buffer_(std::make_unique<boost::asio::streambuf>())
{}

template <class cloud_type,
          class callback,
          class socket_type>
void callable<cloud_type,callback,socket_type>::set_socket(std::unique_ptr<socket_type> arg)
{
    socket_ = std::move(arg);
}

template <class cloud_type,
          class callback,
          class socket_type>
socket_type & callable<cloud_type,callback,socket_type>::get_socket() const
{
    if (!socket_) {
        throw std::runtime_error("no socket for callable");
    }
    return *socket_;
}

template <class cloud_type,
          class callback,
          class socket_type>
boost::asio::streambuf & callable<cloud_type,callback,socket_type>::get_buffer() const
{
    return *buffer_;
}

