#ifndef CLOUD_VISION_DETECTION
#define CLOUD_VISION_DETECTION
#include "includes.ihh"
/**
 * LICENSE HERE
 *
 * @version 0.7.3
 * @date 7 June 2017
 */
#include <rapp/objects.hpp>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/cloud.hpp>
namespace rapp {
namespace cloud {
/**
 * @struct face_detection
 * @brief detect faces in the image
 */
struct face_detection 
: public http_request, 
  public cloud_base<std::vector<rapp::object::face>>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @param image is the input image 
    face_detection(const rapp::object::picture & image);
    
    /// @brief construct without an image - part of a vision batch
    face_detection();
};

/**
 * @struct light_detection 
 * @brief detect the level of light
 */
struct light_detection 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;
    static const std::string uri;

    /// @param image is the picture used
    light_detection(const rapp::object::picture & image);
    
    /// @brief Constructor
    light_detection();
};

/**
 * @struct human_detection
 * @brief detect humans in an image
 */
struct human_detection 
: public http_request, 
  public cloud_base<std::vector<rapp::object::human>>
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /**
     * @param image is a picture object 
     * @param image_format must be defined, e.g.: jpeg, png, gif, etc.
     */
    human_detection(const rapp::object::picture & image);

    /// @brief Constructor without image
    human_detection();
};

/**
 * @struct orb_learn_object
 * @brief learn object gives by the user
 */
struct orb_learn_object 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;
    static const std::string uri;

    /**
     * @param image is the actual object used to be learnt
     * @param name is the name of the object
     */
    orb_learn_object(
                       const rapp::object::picture & image,
                       const std::string name,
                     );

    /// @param name is the name of the object
    orb_learn_object(const std::string name);
};

/**
 * @struct orb_clear_models
 * @brief Clears operational memory for selected user
 */
struct orb_clear_models 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;
    static const std::string uri;

    /// @param user is the user name
    orb_clear_models(const std::string user);
};

/**
 * @struct object_detection_load_models
 * @brief Load one or more models to operational memory
 */
struct orb_load_models 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;
    static const std::string uri;

    /// @param names is the object names to load
    orb_load_models(const std::vector<std::string> names);
};

/**
 * @struct object_detection_find_objects
 * @brief user can provide query image to detect objects
 */
struct orb_find_objects 
: public http_request, 
  public cloud_base<rapp::object::orb_object>
{
    using callback = std::function<void(rapp::object::orb_object)>;
    static const std::string uri;

    /**
     * @param image will be used to find objects
     * @param limit is the limit search to N best matches
     */
    orb_find_objects(
                      const rapp::object::picture & image,
                      const int limit
                    );
    
    /// @param limit is the limit search to N best matches
    orb_find_objects(const int limit);
};

}
}
#endif
