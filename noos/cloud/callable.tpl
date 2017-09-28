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
         >::callable(callback functor,
                     noos::cloud::platform info)
: functor(functor),
  endpoint(info),
  buffer_(std::make_unique<boost::asio::streambuf>()),
  query_(std::make_unique<boost::asio::ip::tcp::resolver::query>(info.address, info.port)),
  io_(std::make_unique<boost::asio::io_service>()),
  resol_(std::make_unique<boost::asio::ip::tcp::resolver>(*io_.get()))
{
    socket([&](auto reply){
            functor(deserialize<cloud_type, 
                                typename cloud_type::data_type>()(reply)); });
    assert(socket_ && query_ && resol_ && io_);
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
  endpoint(info),
  buffer_(std::make_unique<boost::asio::streambuf>()),
  query_(std::make_unique<boost::asio::ip::tcp::resolver::query>(info.address, info.port)),
  io_(std::make_unique<boost::asio::io_service>()),
  resol_(std::make_unique<boost::asio::ip::tcp::resolver>(*io_.get()))
{ 
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
    "template parameter `cloud_type` can't be `cloud_batch` derived class in this context");
    socket([&](auto reply){
            functor(deserialize<cloud_type, 
                                typename cloud_type::data_type>()(reply)); });
    assert(socket_ && query_ && resol_ && io_);
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
  endpoint(info),
  buffer_(std::make_unique<boost::asio::streambuf>()),
  query_(std::make_unique<boost::asio::ip::tcp::resolver::query>(info.address, info.port)),
  io_(std::make_unique<boost::asio::io_service>()),
  resol_(std::make_unique<boost::asio::ip::tcp::resolver>(*io_.get()))
{
    socket([&](auto reply){ object.process(reply); });
    assert(socket_ && query_ && resol_ && io_);
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
  endpoint(info),
  buffer_(std::make_unique<boost::asio::streambuf>()),
  query_(std::make_unique<boost::asio::ip::tcp::resolver::query>(info.address, info.port)),
  io_(std::make_unique<boost::asio::io_service>()),
  resol_(std::make_unique<boost::asio::ip::tcp::resolver>(*io_.get()))
{
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
    "template parameter `cloud_type` can't be `cloud_batch` derived class in this context");
    socket([&](auto reply){
            functor(deserialize<cloud_type, 
                                typename cloud_type::data_type>()(reply)); });
    assert(socket_ && query_ && resol_ && io_);
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
                                            *io_.get(), 
                                            keep_alive,
                                            *buffer_.get());
    assert(socket_ && query_ && resol_ && io_);
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
    assert(socket_ && query_ && resol_ && io_);
    if (!socket_)
        throw std::runtime_error("socket not set");
    if (!io_ || !query_ || !resol_)
        throw std::runtime_error("io, query or resolver not set");
    object.fill_buffer(boost::ref(*buffer_.get()), endpoint);
    socket_->is_connected() ? 
        socket_->send(*query_.get(), *resol_.get(), timeout, *buffer_.get()) :
        socket_->begin(*query_.get(), *resol_.get(), timeout);
    io_->run();
    io_->reset();
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
    assert(io_);
    io_->stop();
}
