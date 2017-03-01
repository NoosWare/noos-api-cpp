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

    /*
    template<typename... Args>
    vision_batch(const rapp::object::picture & image, Args... args)
    : http_request(batch_post__), image__(image)
    {
        http_request::make_multipart_form();
        std::string fname = rapp::misc::random_boundary() + "." + image__.type();
        http_request::add_content("file", fname, image.bytearray());

        misc::for_each_arg([&](auto & obj) { 
            if (obj.is_single_callable()) {
                throw std::runtime_error("object is single callable");
            }
            std::shared_ptr<vision_class> ptr_object = std::make_shared<>(obj); 
            services__["blah"] = ptr_object;
        }, args...);
        for (auto& service : services__) {
            http_request::add_content(service->get_name(), service->make_parameters(), true);
        }
    }
    */

    /**
     * \brief template to add services to the batch
     * \param service is the name of the service ( "face_detection", "human_detection", etc)
     * \param args the arguments needed to do the service call
     */
    template <class service_class, typename... Args>
    void insert_service(Args... args);

    /// \brief End of the request(no more services inserted)
    void end();

    /// \brief URI of vision batch
    static const std::string uri;

private:
    typedef boost::variant<face_detection,
                           qr_recognition,
                           human_detection,
                           door_angle_detection,
                           light_detection,
                           object_detection_learn_object,
                           object_detection_clear_models,
                           object_detection_load_models,
                           object_detection_find_objects> vision_class;

    ///image use for all the vision services
    rapp::object::picture image__;
    ///container of services
    std::map<std::string, vision_class> services__;
};

}
}
#include "vision_batch.imp"
#endif
