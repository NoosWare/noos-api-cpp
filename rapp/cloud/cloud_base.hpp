#ifndef CLOUD_BASE_HPP
#define CLOUD_BASE_HPP
#include "includes.ihh"
#include "deserialize.hpp"
namespace rapp {
namespace cloud {
/**
 * @brief cloud service base class
 * @note defines if it is a single callable service or part of a batch
 * @note it also has the `data_class` object which is used in deserialisation
 * @version 0.7.3
 * @date 2 June 2017
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
template <class data_class> // class cloud_class = derived cloud class
class cloud_base
{
public:
    // using cloud_type = cloud_class;
    using data_type = data_class;

    /**
     * @brief Constructor
     * @param init_value defines if the service is single callable(true) or not
     */
    cloud_base(bool single);
    
    /**
     *  @return boolean to know if it's the service is a 
     *  single call or part of a batch
     */
    bool is_single_callable() const;

    /**
     *  @return std::string with URI for HTTP header
     *  @param uri is the uri of the service
     */
    std::string make_http_uri(std::string uri) const;

    /// @brief get as json
    std::string get_json() const;

protected:
    bool single_callable;
    std::string json;
};

/*
 * Template implementation
 */
template <class return_type>
cloud_base<return_type>::cloud_base(bool single)
: single_callable(single)
{}
 
template <class return_type>
bool cloud_base<return_type>::is_single_callable() const
{
    return single_callable;
}

template <class return_type>
std::string cloud_base<return_type>::make_http_uri(std::string uri) const
{
    return "POST /" + uri + " HTTP/1.1\r\n";
}

template <class return_type>
std::string cloud_base<return_type>::get_json() const
{
    return json;
}

}
}
#endif
