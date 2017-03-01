#ifndef CLOUD_BASE_HPP
#define CLOUD_BASE_HPP
#include "includes.ihh"
namespace rapp
{
namespace cloud
{
/**
 * @brief cloud service base class - 
 * @note defines if it is a single callable service or part of a batch
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class cloud_base
{
public:
    /// \brief Constructor
    cloud_base(bool init_value)
    : single_callable(init_value)
    {}
    
    /**
     *  \return boolean to know if it's the service is a 
     *  single call or part of a batch
     */
    bool is_single_callable() const
    {
        return single_callable;
    }

    std::string make_http_uri(std::string uri) const
    {
        return "POST /" + uri + " HTTP/1.1\r\n";
    }

protected:
    bool single_callable;
};
}
}
#endif
