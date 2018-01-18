#ifndef NOOS_CLOUD_BASE_HPP
#define NOOS_CLOUD_BASE_HPP
#include "includes.ihh"
namespace noos {
namespace cloud {
/**
 * @brief Cloud service base class
 * @note Defines if it is a single callable service or part of a batch.
 * @note It also has the `data_class` object which is used in deserialisation
 * @version 0.7.3
 * @date 2 June 2017
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
template <class data_class>
class cloud_base
{
public:
    // using cloud_type = cloud_class;
    using data_type = data_class;

    /**
     * @brief Constructor
     * @param single_call defines if the service is single callable(true) or not
     */
    cloud_base(bool single_call);
    
    /**
     *  @return Boolean to know if the service is a 
     *  single call or part of a batch
     */
    bool is_single_callable() const;

    /**
     *  @return std::string with URI for HTTP header
     *  @param uri is the uri of the service
     */
    std::string make_http_uri(std::string uri) const;

protected:
    bool single_callable;
};

/**
 * @brief Cloud service batch class
 * @note Defines if it is a batch service
 * @version 0.7.3
 * @date 06.07.2017
 */
struct cloud_batch
{
    unsigned int size;
};

#include "cloud_base.tpl"
}
}
#endif
