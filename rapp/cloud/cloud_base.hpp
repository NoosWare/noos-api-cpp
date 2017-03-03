#ifndef CLOUD_BASE_HPP
#define CLOUD_BASE_HPP
#include "includes.ihh"
#include "deserialize.hpp"
namespace rapp
{
namespace cloud
{
/**
 * @brief cloud service base class - CRTP
 * @note defines if it is a single callable service or part of a batch
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
template <class impl_type, class return_type>
class cloud_base
{
public:
    /**
     * \brief Constructor
     * \param init_value defines if the service is single callable(true) or not
     */
    cloud_base(bool single);
    
    /**
     *  \return boolean to know if it's the service is a 
     *  single call or part of a batch
     */
    bool is_single_callable() const;

    /**
     *  \return std::string with URI for HTTP header
     *  \param uri is the uri of the service
     */
    std::string make_http_uri(std::string uri) const;

    /**
     * \brief process json and call delegate functor
     * \return type specified by inheriting class
     */
    void process(std::string json);

protected:
    bool single_callable;
};

}
}
#include "cloud_base.impl"
#endif
