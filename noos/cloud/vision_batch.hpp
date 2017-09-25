#ifndef NOOS_VISION_BATCH_HPP
#define NOOS_VISION_BATCH_HPP
#include <noos/cloud/includes.ihh>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
#include <noos/cloud/deserialize.hpp>
#include <noos/cloud/vision_base.hpp>
#include <noos/objects.hpp>
namespace noos {
namespace cloud {
/**
 * @brief tied is a convenience pair struct for object + functors used by `vision_batch`
 * @struct tied
 * @version 0.8.0
 * @date 21.09.2017
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
template <class cloud_type>
struct tied
{
    typedef typename cloud_type::callback callback;
    cloud_type object;
    callback functor;
    /// @brief constructor requires only the functor
    tied(callback functor);
    tied(callback functor, cloud_type object);
};

template <class cloud_type>
tied<cloud_type> make_tie(typename cloud_type::callback functor);

/**
 * @brief vision_batch
 * @note creates a call with multiple vision services
 * @version 0.8.0
 * @date 21.09.2017
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 * @note you can only using this class with `vision_base` derived classes
 */
template <class... cloud_pairs>
class vision_batch 
: public http_request, 
  public cloud_base<bool>,
  public cloud_batch
{
public:
    using callback = std::function<void(std::string)>;
    typedef typename vision_batch<cloud_pairs...>::data_type data_types;
    /**
     * @brief construct a vision_batch using a list of `tied` wrappers
     * @param image is a noos::object::picture 
     * @note args will be called in a sequential manner
     */
    vision_batch(const noos::object::picture & image,
                 cloud_pairs... args);
    /** 
     * @brief process the JSON reply and delegate to services
     * This method becomes the specialisation of `deserialize<vision_batch<...>>`,
     * @note this is the callback for `callable` and calls the cloud_pairs functors
     * using a fold expression and tuple unpacking
     */
    void process(std::string json);

protected:
    // expand the tuple of cloud_pairs
    template<std::size_t... batch_size>
    void expand_batch(std::string json, 
                      std::string key,
                      std::index_sequence<batch_size...>);

    // find the cloud_pair (cloud_class and callack and pass the data)
    void find_cloud_type(cloud_pairs... args, 
                          std::string json,
                          std::string key);
   
    const noos::object::picture & image__;
    std::tuple<cloud_pairs...> batch__;
};
}
}
#include "vision_batch.tpl"
#endif
