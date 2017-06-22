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
callable<cloud_type,callback,socket_type> 
    node<socket_type,error_handle>::make(cloud_type object, callback functor)
{
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                  "`cloud_type` cannot be a `cloud_batch` derived class");
    auto result = callable<cloud_type,callback,socket_type>(object, functor);
    result.socket(
        [&](auto reply){ functor(deserialize<cloud_type, typename cloud_type::data_type>()(reply)); }, 
        [&](auto e){ error_handle()(e); }, 
        io_,
        true);
    return result;
}

template <class socket_type,
          class error_handle>
template <class cloud_type, 
          class callback,
          class... parameters>
callable<cloud_type,callback,socket_type>  
    node<socket_type,error_handle>::make(parameters... args, callback functor)
{
    auto result = callable<cloud_type,callback,socket_type>(std::forward<parameters...>(args)..., functor);
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                  "`cloud_type` cannot be a `cloud_batch` derived class");
    result.socket(
        [&](auto reply){ functor(deserialize<cloud_type, typename cloud_type::data_type>(reply)); }, 
        [&](auto e){ error_handle()(e); }, 
        io_,
        true);
    return result;
}

template <class socket_type,
          class error_handle>
template <class... cloud_pairs>
callable<vision_batch<cloud_pairs...>,
         typename vision_batch<cloud_pairs...>::callback,
         socket_type>
    node<socket_type,error_handle>::make(const noos::object::picture & image, cloud_pairs... args)
{
	callable<vision_batch<cloud_pairs...>, 
                           typename vision_batch<cloud_pairs...>::callback,
                           socket_type> result;
    result = callable<vision_batch<cloud_pairs...>, 
                           typename vision_batch<cloud_pairs...>::callback,
                           socket_type>( 
                                   vision_batch<cloud_pairs...>(image, std::forward<cloud_pairs>(args)...),
                                   [&](auto reply){ result.object.process(reply); });
    assert(result.functor);
    using actual_class = typename decltype(result.object)::value_type;
    static_assert(std::is_base_of<cloud_batch, actual_class>::value,
                  "`cloud_type` must be a `cloud_batch` derived class");
    result.socket(
        [&](auto reply){ result.functor(reply); }, 
        [&](auto e){ error_handle()(e); }, 
        io_,
        true);
    return std::move(result);
}

template <class socket_type,
          class error_handle>
template <class... callables> 
std::tuple<callables...> node<socket_type,error_handle>::pack(callables... args)
{
    misc::for_each_arg([&](auto & callbl) {
        using cloud_type = typename decltype(callbl.object)::value_type;
        static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                      "`cloud_type` cannot be a `cloud_batch` derived class");
        callbl.socket(
           [&](auto reply){ callbl.functor(deserialize<cloud_type, typename cloud_type::data_type>(reply)); },
           [&](auto e){ error_handle()(e); }, 
           io_);
    }, args...);
    return std::make_tuple((args)...);
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
void node<socket_type,error_handle>::call(callable<cloud_type,callback,socket_type> & arg)
{
    static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                  "`cloud_type` cannot be a `cloud_batch` derived class");
    assert(arg.object.is_single_callable());
    if (!arg.object.is_single_callable()) {
        throw std::runtime_error("cannot call a non-single-callable");
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
        using cloud_type = typename decltype(arg.object)::value_type;
        static_assert(!std::is_base_of<cloud_batch, cloud_type>::value,
                      "`cloud_type` cannot be a `cloud_batch` derived class");
        assert(!arg.object.is_single_callable());
        if (!arg.object.is_single_callable()) {
            throw std::runtime_error("cannot call a non-single-callable");
        }
        arg.send(query_, resol_, timeout_, info_);
    }, args...);
    run_reset();
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
callable<cloud_type,callback,socket_type> 
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
callable<cloud_type,callback,socket_type> 
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
