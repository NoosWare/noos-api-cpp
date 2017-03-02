#ifndef VISION_BATCH_HPP
#define VISION_BATCH_HPP

#include <rapp/cloud/includes.ihh>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/cloud/asio/platform.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/cloud/vision_recognition.hpp>
#include <rapp/misc/misc.hpp>

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
template <typename... services>
class vision_batch 
: public http_request, public cloud_base 
{
public:
    /**
     * \brief Constructor
     * \param image use for the batch
     */
    vision_batch(
                 const rapp::object::picture & image,
                 services... args
                )
    : http_request(uri), 
      cloud_base(true),
      image__(image)
    {
        /*
        http_request::make_multipart_form();
        std::string fname = rapp::misc::random_boundary() + "." + image__.type();
        http_request::add_content("file", fname, image.bytearray());
        */
        services__ = std::make_tuple((args)...);
        //std::get<index__[obj.uri]>(services__);
    }

    /// \brief Deserialise of every single object in services__
    void deserialise(std::string json_str);

    /// \brief URI of vision batch
    std::string uri() const
    {
        return make_http_uri("vision_batch");
    }

private:
    ///image use for all the vision services
    const rapp::object::picture & image__;
    /// named index
    std::map<std::string, unsigned int> index__;
    /// sub-services
    std::tuple<services...> services__;
};

}
}
//#include "vision_batch.imp"
#endif
