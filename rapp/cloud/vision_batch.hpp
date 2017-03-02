#ifndef VISION_BATCH_HPP
#define VISION_BATCH_HPP

#include <rapp/cloud/includes.ihh>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/cloud/asio/platform.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/cloud/vision_recognition.hpp>

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

    /**
     * \brief template to add services to the batch
     * \param service is the name of the service ( "face_detection", "human_detection", etc)
     * \param args the arguments needed to do the service call
     */
    template <class service_class, typename... Args>
    void insert_service(Args... args);

    /// \brief Deserialise of every single object in services__
    void deserialise(std::string json_str);

    /// \brief End of the request(no more services inserted)
    void end();

    /// \brief URI of vision batch
    static const std::string uri;

private:
    /*
    typedef boost::variant<
                           face_detection,
                           qr_recognition,
                           human_detection,
                           door_angle_detection,
                           light_detection,
                           object_detection_learn_object,
                           object_detection_clear_models,
                           object_detection_load_models,
                           object_detection_find_objects> vision_class;
    */
    ///image use for all the vision services
    rapp::object::picture image__;
    ///container of services
    std::map<std::string, boost::any> services__;
};

}
}
#include "vision_batch.imp"
#endif
