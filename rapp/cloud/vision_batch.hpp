#ifndef VISION_BATCH_HPP
#define VISION_BATCH_HPP

#include <rapp/cloud/includes.ihh>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/cloud/cloud_base.hpp>
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
     * \brief virtual deserialise function
     * \param JSON string
     */
    virtual void deserialise (std::string json) = 0;

    /**
     * \brief virtual fill_buffer
     * \param buffer
     * \param info is the platform information
     */ 
    virtual void fill_buffer(
                              boost::asio::streambuf & buffer,
                              rapp::cloud::platform info
                            ) = 0;


};
    
/**
 * @brief vision_batch
 * @note creates a call with multiple vision services
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class vision_batch :public http_request
{
public:

    /**
     * \brief Constructor
     * \param image use for the batch
     */
    vision_batch(const rapp::object::picture & image)
    : http_request(batch_post__),
      image__(image)
    {
        http_request::make_multipart_form();
        std::string fname = rapp::misc::random_boundary() + "." + image__.type();
        http_request::add_content("file", fname, image.bytearray());
        //http_request::close(); when?
    };

    /**
     * \brief template to add services to the batch
     * \param
     */
    template <typename vision_service, typename... Args>
    void insert(Args... args)   
    {
        static_assert(std::is_base_of<vision_class, vision_service>::value,
                     "vision_batch::insert param must be a vision_batch type"); 
        auto object = vision_service(args...);
        if (object.is_single_callable()) {
            throw std::runtime_error("Wrong constructor for using it in vision batch");
        }
        else {
            services__.push_back(object); 
        }
            
    }

    void end()
    {
        http_request::close();
    };

    std::vector<std::shared_ptr<vision_class>> get_services()
    {
        return services__;
    }

private:
    ///image use for all the vision services
    rapp::object::picture image__;
    ///HTTP header name
    const std::string batch_post__ = "POST /vision_batch HTTP/1.1\r\n";
    ///container of services
    std::vector<std::shared_ptr<vision_class>> services__; //not working

};

}
}

#endif
