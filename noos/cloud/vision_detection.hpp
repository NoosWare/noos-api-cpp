#ifndef NOOS_CLOUD_VISION_DETECTION
#define NOOS_CLOUD_VISION_DETECTION
/*
 * LICENSE HERE
 */
#include "includes.ihh"
#include <noos/objects.hpp>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
#include <noos/cloud/vision_base.hpp>
namespace noos {
namespace cloud {
/**
 * @struct face_detection
 * @brief detect faces in the image
 */
struct face_detection 
: public http_request, 
  public cloud_base<std::vector<noos::object::face>>,
  public vision_base
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @param image is the input image 
    face_detection(const noos::object::picture & image);

    /// @brief construct without an image - part of a vision batch
    face_detection();
};

/**
 * @struct light_detection 
 * @brief detect the level of light
 */
struct light_detection 
: public http_request, 
  public cloud_base<int>,
  public vision_base
{
    using callback = std::function<void(int)>;
    static const std::string uri;

    /// @param image is the picture used
    light_detection(const noos::object::picture & image);

    /// @brief Constructor
    light_detection();
};

/**
 * @struct human_detection
 * @brief detect humans in an image
 */
struct human_detection 
: public http_request, 
  public cloud_base<std::vector<noos::object::human>>,
  public vision_base
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /**
     * @param image is a picture object 
     * @param image_format must be defined, e.g.: jpeg, png, gif, etc.
     */
    human_detection(const noos::object::picture & image);

    /// @brief Constructor without image
    human_detection();
};

/**
 * @struct gender_detection
 * @brief detect gender of person in an image
 * @note data type passed back is an `std::string`
 */
struct gender_detection 
: public http_request, 
  public cloud_base<std::string>,
  public vision_base
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    /**
     * @param image is a picture object 
     * @param image_format must be defined, e.g.: jpeg, png, gif, etc.
     */
    gender_detection(const noos::object::picture & image);

    /// @brief Constructor without image
    gender_detection();
};

/**
 * @struct age_detection
 * @brief detect age range of person in an image
 * @note data type passed back is `std::vector<std::pair<std::string,float>>`
 */
struct age_detection 
: public http_request, 
  public cloud_base<std::vector<std::pair<std::string,float>>>,
  public vision_base
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;
    /**
     * @param image is a picture object 
     * @param image_format must be defined, e.g.: jpeg, png, gif, etc.
     */
    age_detection(const noos::object::picture & image);

    /// @brief Constructor without image
    age_detection();
};

/**
 * @struct orb_learn_object
 * @brief learn object gives by the user
 */
struct orb_learn_object 
: public http_request, 
  public cloud_base<int>,
  public vision_base
{
    using callback = std::function<void(int)>;
    static const std::string uri;

    /**
     * @param image is the actual object used to be learnt
     * @param name is the name of the object
     */
    orb_learn_object(
                       const noos::object::picture & image,
                       const std::string name
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
  public cloud_base<noos::object::orb_object>,
  public vision_base
{
    using callback = std::function<void(noos::object::orb_object)>;
    static const std::string uri;

    /**
     * @param image will be used to find objects
     * @param limit is the limit search to N best matches
     */
    orb_find_objects(
                      const noos::object::picture & image,
                      const int limit
                    );

    /// @param limit is the limit search to N best matches
    orb_find_objects(const int limit);
};

}
}
#endif
