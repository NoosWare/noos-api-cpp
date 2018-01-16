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
#include <noos/cloud/vision_batch.hpp>
namespace noos {
namespace cloud {
/**
 * @struct age_detection
 * @brief detect age range of person in an image
 * @version 0.8.0
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
    age_detection(noos::object::picture image);

    /// @brief Constructor without image
    age_detection();
};
/**
 * @struct face_detection
 * @brief detect faces in the image
 * @version 0.7.0
 * @note data type passed back is `std::vector<noos::object::face>`
 */
struct face_detection 
: public http_request, 
  public cloud_base<std::vector<noos::object::face>>,
  public vision_base
{
    using callback = std::function<void(data_type)>;
    static const std::string uri;

    /// @param image is the input picture object 
    face_detection(noos::object::picture image);

    /// @brief construct without an image - part of a vision batch
    face_detection();
};
/**
 * @struct gender_detection
 * @brief detect gender of person in an image
 * @version 0.8.0
 * @note data type passed back is an `std::string`
 */
struct gender_detection 
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
    gender_detection(noos::object::picture image);

    /// @brief Constructor without image
    gender_detection();
};
/**
 * @struct human_detection
 * @brief detect humans in an image
 * @version 0.7.0
 * @note data type passed back is an `std::vector<noos::object::human>`
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
    human_detection(noos::object::picture image);

    /// @brief Constructor without image
    human_detection();
};
/**
 * @struct orb_add_model
 * @brief learn object gives by the user
 * @version 0.8.0
 * @note data type passed back is an `bool`
 */
struct orb_add_model 
: public http_request, 
  public cloud_base<bool>,
  public vision_base
{
    using callback = std::function<void(bool)>;
    static const std::string uri;

    /**
     * @param image is the actual object used to be learnt
     * @param name is the name of the object
     */
    orb_add_model(
                       noos::object::picture image,
                       const std::string name
                     );

    /// @param name is the name of the object
    orb_add_model(const std::string name);
};

/**
 * @struct orb_del_model
 * @brief Clears operational memory for selected user
 * @version 0.8.0
 * @note data type passed back is an `bool`
 */
struct orb_del_model
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(bool)>;
    static const std::string uri;

    /// @param user is the user name
    orb_del_model(const std::string model);
};

/**
 * @struct orb_query
 * @brief user can provide query image to detect objects
 * @version 0.8.0
 * @note data type passed back is an `std::vector<noos::object::point2d<float>>`
 */
struct orb_query 
: public http_request, 
  public cloud_base<std::vector<noos::object::point2d<float>>>,
  public vision_base
{
    using callback = std::function<void(
                            std::vector<noos::object::point2d<float>>)>;
    static const std::string uri;

    /**
     * @brief constructor using an image, a model
     *        and a threshold
     * @param image will be used to find objects
     * @param model is the filename of the model 
     *        which is going to be loaded
     * @param threshold is the minimum distance between 
     *        keypoints
     */
    orb_query(
                      noos::object::picture image,
                      const std::string model,
                      const float threshold
                    );

    /// @brief constructor without image for using it
    ///        with vision_batch
    /// @param model is the filename of the model
    /// @param threshold is teh minimun distance between 
    ///         keypoints
    orb_query(const std::string model,
                     const float threshold);
};

}
}
#endif
