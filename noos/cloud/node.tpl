/* 
 * Template Implementations
 */
template <class socket_type,
          class error_handle>
node<socket_type,error_handle>::node(noos::cloud::platform info)
: info_(info), query_(info.address, info.port), 
  io_(), resol_(io_), timeout_(2)
{}

template <class socket_type,
          class error_handle>
node<socket_type,error_handle>::node(json json_object)
: info_(platform()(json_object)), 
  query_(info_.address, info_.port), 
  io_(), resol_(io_), timeout_(2)
{}

template <class socket_type,
          class error_handle>
node<socket_type,error_handle>::node(std::string filename)
: info_(platform()(filename)), 
  query_(info_.address, info_.port), 
  io_(), resol_(io_), timeout_(2)
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
void node<socket_type,error_handle>::run_reset()
{
    io_.run();
    io_.reset();
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
callable<cloud_type,callback,socket_type,error_handle> 
    node<socket_type,error_handle>::make(cloud_type object, callback functor)
{
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                  "`cloud_type` cannot be a `cloud_batch` derived class in this method");
    auto result = callable<cloud_type,callback,socket_type,error_handle>(object, functor);
    result.socket(
        [&](auto reply){ functor(deserialize<cloud_type, typename cloud_type::data_type>()(reply)); }, 
        io_,
        true);
    return result;
}

template <class socket_type,
          class error_handle>
template <class cloud_type, 
          class callback,
          class... parameters>
callable<cloud_type,callback,socket_type,error_handle>  
    node<socket_type,error_handle>::make(parameters... args, callback functor)
{
    auto result = callable<cloud_type,callback,socket_type,error_handle>(
                                std::forward<parameters...>(args)..., functor);
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                  "`cloud_type` cannot be a `cloud_batch` derived class in this method");
    result.socket(
        [&](auto reply){ functor(deserialize<cloud_type, typename cloud_type::data_type>(reply)); }, 
        io_,
        true);
    return result;
}

template <class socket_type,
          class error_handle>
template <class... cloud_pairs>
callable<vision_batch<cloud_pairs...>,
         typename vision_batch<cloud_pairs...>::callback,
         socket_type, error_handle>
    node<socket_type,error_handle>::make(const noos::object::picture & image, cloud_pairs... args)
{
	callable<
        vision_batch<cloud_pairs...>, 
        typename vision_batch<cloud_pairs...>::callback, 
        socket_type, error_handle> 
        result = callable<vision_batch<cloud_pairs...>, 
                          typename vision_batch<cloud_pairs...>::callback,
                          socket_type, error_handle>( 
                               vision_batch<cloud_pairs...>(image, (args)...),
                               [&](auto reply){ result.object.process(reply); }
                            );
    assert(result.functor);
    result.socket(
        [&](auto reply){ result.functor(reply); }, 
        io_,
        false);
    return result;
}

template <class socket_type,
          class error_handle>
template <class... callables> 
std::tuple<callables...> node<socket_type,error_handle>::pack(callables... args)
{
    misc::for_each_arg([&](auto & callbl) {
        using cloud_type = typename decltype(callbl.object)::value_type;
        static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                      "`cloud_type` cannot be a `cloud_batch` derived class in this method");
        callbl.socket(
           [&](auto reply){ callbl.functor(deserialize<cloud_type, typename cloud_type::data_type>(reply)); },
           io_);
    }, args...);
    return std::make_tuple((args)...);
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
void node<socket_type,error_handle>::call_once(cloud_type object, callback functor)
{
    assert(object.is_single_callable());
    if (!object.is_single_callable()) {
        throw std::runtime_error("cannot call a non-single callable directly");
    }
    boost::asio::streambuf buffer;
    object.fill_buffer(boost::ref(buffer), info_); 
    auto socket = std::make_unique<socket_type>(
            [&](auto reply){ functor(deserialize<cloud_type, typename cloud_type::data_type>()(reply)); }, 
            io_, 
            false,
            buffer);
    socket->begin(query_, resol_, timeout_);
    run_reset();
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class... parameters,
          class callback>
void node<socket_type,error_handle>::call_once(parameters... args, callback functor)
{
    auto object = cloud_type(std::forward<parameters...>(args)...);
    call_once(object, functor);
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
void node<socket_type,error_handle>::call(callable<cloud_type,callback,socket_type,error_handle> & arg)
{
    assert(arg.object.is_single_callable());
    if (!arg.object.is_single_callable()) {
        throw std::runtime_error("cannot call a non-single callable directly");
    }
    arg.send(query_, resol_, timeout_, info_);
    run_reset();
}

template <class socket_type,
          class error_handle>
template <class... callables>
void node<socket_type,error_handle>::call(callables & ...args)
{
    misc::for_each_arg([&](auto & arg) {
        assert(!arg.object.is_single_callable());
        if (!arg.object.is_single_callable()) {
            throw std::runtime_error("cannot call a non-single callable directly");
        }
        arg.send(query_, resol_, timeout_, info_);
    }, args...);
    run_reset();
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
callable<cloud_type,callback,socket_type,error_handle> 
    node<socket_type,error_handle>::make_call(cloud_type object, callback functor)
{
    auto result = make(object, functor);
    call(result);
    return result;
}

template <class socket_type,
          class error_handle>
template <class cloud_type, 
          class callback,
          class... parameters>
callable<cloud_type,callback,socket_type,error_handle> 
    node<socket_type,error_handle>::make_call(parameters... args, callback functor)
{
    auto result = make(std::forward<parameters...>(args)..., functor);
    call(result);
    return std::move(result);
}

template <class socket_type,
          class error_handle>
template <class... callables>
std::tuple<callables...> node<socket_type,error_handle>::pack_call(callables ... args)
{
   auto tuple = pack(std::forward<callables...>(args)...);
   call(tuple);
   return std::move(tuple);
}
