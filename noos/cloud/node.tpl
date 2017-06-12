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
template <class cloud_type,
          class callback>
callable<cloud_type,callback,socket_type> 
    node<socket_type,error_handle>::make_one(cloud_type object, callback functor)
{
    static_assert(!std::is_base_of<cloud_batch, arg.object>::value);
    auto result = callable<cloud_type,socket_type,callback>(object, callback);
    result.set_socket(std::move(std::make_unique<socket_type>(
        [&](auto reply) {
            functor(deserialize<cloud_type, object::data_type>(reply)); 
        }, error_handle, io_, result.buffer)));
    return std::move(result);
}

template <class socket_type,
          class error_handle>
template <class cloud_type, 
          class callback,
          typename... parameters>
callable<cloud_type,callback,socket_type>  
    node<socket_type,error_handle>::make_one(parameters... args, callback functor)
{
    static_assert(!std::is_base_of<cloud_batch, arg.object>::value);
    auto result = callable<cloud_type,socket_type,callback>(
                                       std::forward<parameters>(args...), callback);
    result.set_socket(std::move(std::make_unique<asio_http>(
        [&](auto reply) {
            functor(deserialize<cloud_type, object::data_type>(reply)); 
        }, error_handle, io_, result.buffer)));
    return std::move(result);
}

template <class socket_type,
          class error_handle>
template <typename... callables> 
std::tuple<callables...> node<socket_type,error_handle>::make_many(callables... args)
{
    // QUESTION: will this set the objects iterated by reference, and then assign the socket?
    //           or is this wishful thinking?
    //
    misc::for_each_arg([&](auto & callbl) {
        static_assert(!std::is_base_of<cloud_batch, callbl.object::cloud_type>::value);
        callbl.set_socket(std::move(
           std::make_unique<asio_http>([&](auto reply) {
               callbl.functor(deserialize<callbl::cloud_type, callbl.object::data_type>(reply)); 
           }, error_handle, io_, callbl.buffer)));
    }, args...);
    return std::make_tuple((args)...);
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
void node<socket_type,error_handle>::call_one(callable<cloud_type,callback,socket_type> & arg)
{
    static_assert(!std::is_base_of<cloud_batch, arg.object>::value);
    static_assert(!arg.is_single_callable());
    arg.buffer.consume(arg.buffer.size() + 1);
    arg.get_socket().begin(query_, resol_, timeout_);
    io_.run();
    io_.reset();
}

template <class socket_type,
          class error_handle>
template <typename... callables>
void node<socket_type,error_handle>::call_many(callables... & args)
{
    misc::for_each_arg([&](auto & arg) {
        static_assert(!arg.object.is_single_callable()); 
        static_assert(!std::is_base_of<cloud_batch, arg.object>::value);
        arg.buffer.consume(arg.buffer.size() + 1);
        arg.get_socket().begin(query_, resol_, timeout_);
    }, args...);
    io_.run();
    io_.reset();
}

template <class socket_type,
          class error_handle>
template <class cloud_type,
          class callback>
callable<cloud_type,socket_type,callback> 
    node<socket_type,error_handle>::make_call_one(cloud_type object, callback)
{
    auto result = make_one(object, callback);
    call_one(result);
    return std::move(result);
}

template <class socket_type,
          class error_handle>
template <class cloud_type, 
          class callback,
          typename... parameters>
callable<cloud_type,callback,socket_type> 
    node<socket_type,error_handle>::make_call_one(parameters... args, callback functor)
{
    auto result = make_one(std::forward<parameters>(args...), functor);
    call_one(result);
    return std::move(result);
}
