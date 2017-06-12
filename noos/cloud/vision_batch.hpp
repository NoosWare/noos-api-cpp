#ifndef VISION_BATCH_HPP
#define VISION_BATCH_HPP

#include <rapp/cloud/includes.ihh>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/objects.hpp>
#include <rapp/cloud.hpp>

namespace rapp {
namespace cloud {

/**
 * @brief vision_batch
 * @note creates a call with multiple vision services
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
template <class... cloud_pairs>
class vision_batch 
: public http_request, 
  public cloud_base<bool>,
  public cloud_batch
{
public:

    ///
    vision_batch(
                  const rapp::object::picture & image,
                  cloud_pairs... args,
                );
   
    /// \brief process the JSON reply and delegate to services
    // DEPRECATED
    // This becomes the specialisation of deserialize<vision_batch, 
    void process(std::string json);

    /// \brief expand batch type
    template<std::size_t... batch_size>
    void expand_batch(
                      std::string json, 
                      std::string key,
                      std::index_sequence<batch_size...>
                     );

    /// \brief
    void find_cloud_type(
                          services... args, 
                          std::string json,
                          std::string key
                        );
   
private:
    const rapp::object::picture & image__;
    std::tuple<cloud_pairs...> batch__;
};
}
}
//#include "vision_batch.impl"
#endif
