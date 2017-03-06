#ifndef VISION_BATCH_HPP
#define VISION_BATCH_HPP

#include <rapp/cloud/includes.ihh>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/objects.hpp>
#include <rapp/cloud.hpp>

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
  public cloud_base<vision_batch<services...>,bool>
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
    void process(std::string json);

    /// \brief expand batch type
    template<std::size_t... batch_size>
    void expand_batch(
                      std::string json, 
                      std::string key,
                      std::index_sequence<batch_size...>
                     ) 
    {
        find_process(std::get<batch_size>(batch__)..., json, key);
    }

    /// \brief
    void find_process(
                       services... args, 
                       std::string json,
                       std::string key
                     );
   
private:
    /// \brief image use for all the vision services
    const rapp::object::picture & image__;
    /// \brief batch services
    std::tuple<services...> batch__;
};

}
}
#include "vision_batch.impl"
#endif
