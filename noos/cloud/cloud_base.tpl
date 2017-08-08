/*
 * Template implementation
 */

template <class data_class> 
cloud_base<data_class>::cloud_base(bool single_call)
: single_callable(single_call)
{}

template <class data_class>
inline bool cloud_base<data_class>::is_single_callable() const
{
    return single_callable;
}

template <class data_class> 
std::string cloud_base<data_class>::make_http_uri(std::string uri) const
{
    return "POST /" + uri + " HTTP/1.1\r\n";
}

