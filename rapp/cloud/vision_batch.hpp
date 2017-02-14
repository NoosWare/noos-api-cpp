#ifndef VISION_BATCH_HPP
#define VISION_BATCH_HPP

#include <rapp/cloud/includes.ihh>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/cloud/asio/platform.hpp>

namespace rapp
{
namespace cloud
{
/**
 * @brief vision_class 
 * @note defines if it is part of vision service 
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct vision_class
{
    /**
     * \brief virtual deserialise function to a vision batch
     * \param JSON string
     */
    virtual void deserialise(nlohmann::json json) const = 0;

    /**
     * \brief return a string of the cloud JSON parameters
     */
    virtual std::string make_parameters() const = 0;
};
    
/**
 * @brief vision_batch
 * @note creates a call with multiple vision services
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class vision_batch : public http_request
{
public:

    /**
     * \brief Constructor
     * \param image use for the batch
     */
    vision_batch(const rapp::object::picture & image);

    /**
     * \brief template to add services to the batch
     * \param service is the name of the service ( "face_detection", "human_detection", etc)
     * \param args the arguments needed to do the service call
     */
    template <class service_class, typename... Args>
    void insert(std::string service, Args... args)   
    {
        static_assert(std::is_base_of<vision_class, service_class>::value,
                     "param must be a vision_class"); 
        auto object = std::make_shared<service_class>(args...);
        if (object->is_single_callable()) {
            throw std::runtime_error("object is single callable");
        }
        services__[service] = object;
        http_request::add_content(service, object->make_parameters(), true);
    }

    /**
     * \brief deserialise method 
     * \param JSON reply data 
     */
    void deserialise(std::string json_str);

    /// \brief End of the request(no more services inserted)
    void end();

private:
    ///image use for all the vision services
    rapp::object::picture image__;
    ///HTTP header name
    static const std::string batch_post__;
    ///container of services
    std::map<std::string, std::shared_ptr<vision_class>> services__;
};

}
}

#endif
