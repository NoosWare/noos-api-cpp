#ifndef NOOS_VISION_BATCH_HPP
#define NOOS_VISION_BATCH_HPP
#include <noos/cloud/includes.ihh>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
#include <noos/cloud/cloud_batch.hpp>
#include <noos/objects.hpp>
namespace noos {
namespace cloud {
/**
 * @brief vision_batch
 * @note creates a call with multiple vision services
 * @version 0.7.3
 * @date 09.02.0217
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 *
 * @note the variadic template parameter `cloud_pairs` expects
 *       a sequence of `std::pair<cloud_class, callback>`.
 *       anything else won't compile or worse...
 */
template <class... cloud_pairs>
class vision_batch 
: public http_request, 
  public cloud_base<bool>,
  public cloud_batch
{
public:
    using callback = std::function<void(std::string)>;

    ///
    vision_batch(
                  const noos::object::picture & image,
                  cloud_pairs... args
                );
   
    /// \brief process the JSON reply and delegate to services
    // This becomes the specialisation of deserialize<vision_batch, 
    // NOTE: this is the callback for `callable` and calls the cloud_pairs
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
                          cloud_pairs... args, 
                          std::string json,
                          std::string key
                        );
   
private:
    const noos::object::picture & image__;
    std::tuple<cloud_pairs...> batch__;
};
}
}
//#include "vision_batch.impl"
#endif
