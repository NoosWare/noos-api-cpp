/*
 * Template implementation
 */
template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
          >
callable<cloud_type,
         keep_alive,
         socket_type,
         error_handle
         >::callable(noos::cloud::platform info)
: buffer_(std::make_unique<boost::asio::streambuf>()),
  endpoint(info),
  query_(info.address, info.port),
  io_(),
  resol_(io_)
{
    socket([&](auto reply){
            functor(deserialize<cloud_type, 
                                typename cloud_type::data_type>()(reply)); });
}

template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
          >
callable<cloud_type,
         keep_alive,
         socket_type,
         error_handle>
         ::callable(cloud_type object,
                    callback functor,
                    noos::cloud::platform info)
: object(object), 
  functor(functor), 
  buffer_(std::make_unique<boost::asio::streambuf>()),
  endpoint(info),
  query_(info.address, info.port),
  io_(),
  resol_(io_)
{ 
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                  "`cloud_type` cannot be a `cloud_batch` derived class in this method");
    socket([&](auto reply){
            functor(deserialize<cloud_type, 
                                typename cloud_type::data_type>()(reply)); });
}

template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
         >
template <typename... parameters>
callable<cloud_type,
         keep_alive,
         socket_type,
         error_handle
        >::callable(vision_batch<parameters...> arg,
                    noos::cloud::platform info)
: object(vision_batch<parameters...>(arg)), 
  buffer_(std::make_unique<boost::asio::streambuf>()),
  endpoint(info),
  query_(info.address, info.port),
  io_(),
  resol_(io_)
{
    socket([&](auto reply){ object.process(reply); });
}

template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
         >
template <typename... parameters>
callable<cloud_type,
         keep_alive,
         socket_type,
         error_handle
        >::callable(parameters... args,
                    callback functor,
                    noos::cloud::platform info)
: object(args...), 
  functor(functor),
  buffer_(std::make_unique<boost::asio::streambuf>()),
  endpoint(info),
  query_(info.address, info.port),
  io_(),
  resol_(io_)
{
    socket([&](auto reply){
            functor(deserialize<cloud_type, 
                                typename cloud_type::data_type>()(reply)); });
}

template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
         >
void callable<cloud_type,
              keep_alive,
              socket_type,
              error_handle
             >::socket(std::function<void(std::string)> cloud_functor)
{
    socket_ = std::make_unique<socket_type>(cloud_functor, 
                                            [&](auto e){ error_handle()(e); }, 
                                            io_, 
                                            keep_alive,
                                            *buffer_.get());
    assert(socket_);
}

template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
         >
void callable<cloud_type,
              keep_alive,
              socket_type,
              error_handle
             >::send(unsigned int timeout)
{
    assert(socket_);
    if (!socket_) {
        throw std::runtime_error("socket not set");
    }
    object.fill_buffer(boost::ref(*buffer_.get()), endpoint);
    socket_->is_connected() ? 
        socket_->send(query_, resol_, timeout, *buffer_.get()) :
        socket_->begin(query_, resol_, timeout);
    io_.run();
    io_.reset();
}

template <class cloud_type,
          bool  keep_alive,
          class socket_type,
          class error_handle
         >
void callable<cloud_type,
              keep_alive,
              socket_type,
              error_handle
             >::stop()
{
    io_.stop();
}
