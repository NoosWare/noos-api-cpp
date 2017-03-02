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
template <class... services> 
class vision_batch 
: public http_request, 
  public cloud_base<vision_batch<services...>,void>
{
public:
    /**
     * \brief Constructor
     * \param image use for the batch
     */
    vision_batch(
                  const rapp::object::picture & image,
                  services... args
                );
   
    /// \brief process the JSON reply and delegate to services
    void deserialise(std::string json);

private:
    /// \brief image use for all the vision services
    const rapp::object::picture & image__;
    /// \brief named index map
    std::map<std::string, unsigned int> index__;
    /// \brief batch services
    std::tuple<services...> batch__;
};

}
}
#include "vision_batch.impl"
#endif
