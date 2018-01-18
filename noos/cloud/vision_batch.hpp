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
 * @brief Tied is a convenience pair struct for object + functors used by `vision_batch`
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
    /// @brief Constructor requires only the functor
    tied(callback functor);
    /// @brief Constructor using the callback and 
    ///        the object
    tied(callback functor, cloud_type object);
};

/// @brief simple helper - not really needed
template <class cloud_type>
tied<cloud_type> make_tie(typename cloud_type::callback functor);

/**
 * @brief vision_batch
 * @note Creates a call with multiple vision services for the same image
 * @version 0.8.0
 * @date 21.09.2017
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 * @note you can only using this class with `vision_base` derived classes
 */
template <class... ties>
class vision_batch 
: public http_request, 
  public cloud_base<bool>,
  public cloud_batch
{
public:
    using callback = std::function<void(std::string)>;
    typedef typename vision_batch<ties...>::data_type data_types;
    /**
     * @brief Construct a vision_batch using a list of `tied` wrappers
     * @param image is a noos::object::picture  @see noos::object::picture
     * @note `args` will be called in a sequential manner
     */
    vision_batch(noos::object::picture image,
                 ties... args);
    /** 
     * @brief Process the JSON reply and delegate to services
     * This method becomes the specialisation of `deserialize<vision_batch<...>>`,
     * @note this is the callback for `callable` and calls the ties functors
     * using a fold expression and tuple unpacking
     */
    void process(std::string json);

protected:
    // expand the tuple of ties
    template<std::size_t... batch_size>
    void expand_batch(std::string json, 
                      std::string key,
                      std::index_sequence<batch_size...>);

    // find the cloud_pair (cloud_class and callack and pass the data)
    void find_cloud_type(ties... args, 
                          std::string json,
                          std::string key);
   
    noos::object::picture image__;
    std::tuple<ties...> batch__;
};
}
}
#include "vision_batch.tpl"
#endif
