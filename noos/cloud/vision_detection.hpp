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
 * @brief Detect age range of person in an image
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
    /// @brief Constructor using an image of a face
    /// @param image is a picture object reference @see noos::object::picture
    /// @warning For this service, the face of the image has to be already cropped.
    ///          Otherwise, the result will be random.
    age_detection(noos::object::picture image);

    /// @brief Constructor without image - part of a vision_batch
    age_detection();
};
/**
 * @struct face_detection
 * @brief Service request to detect faces in a image
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

    /// @brief Constructor using an image
    /// @param image is the input picture object @see noos::object::picture
    face_detection(noos::object::picture image);

    /// @brief Constructor without an image - part of a vision_batch
    face_detection();
};
/**
 * @struct gender_detection
 * @brief Detect gender of person in an image
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

    /// @brief Constructor using an image of a face
    /// @param image is a picture object reference @see noos::object::picture
    /// @warning For this service, the face of the image has to be already cropped.
    ///          Otherwise, the result will be random.
    gender_detection(noos::object::picture image);

    /// @brief Constructor without image - part of a vision_batch
    gender_detection();
};
/**
 * @struct human_detection
 * @brief Service request to detect humans in an image
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

    /// @brief Constructor using an image of a face
    /// @param image is a picture object reference @see noos::object::picture
    human_detection(noos::object::picture image);

    /// @brief Constructor without image - part of a vision_batch
    human_detection();
};
/**
 * @struct orb_add_model
 * @brief Service request to learn the object gives by the user.
 * @version 0.8.0
 * @note data type passed back is an `bool`
 * @note The model only will be use for ORB requests.
 */
struct orb_add_model 
: public http_request, 
  public cloud_base<bool>,
  public vision_base
{
    using callback = std::function<void(bool)>;
    static const std::string uri;

    ///@brief Constructor using the following parameters:
    ///@param image is the actual object used to be learnt
    ///@param name is the name with which the model is going to be saved
    orb_add_model(
                   noos::object::picture image,
                   const std::string name
                 );

    /// @brief Constructor without image - part of a vision_batch
    /// @param name is the name of the object
    orb_add_model(const std::string name);
};

/**
 * @struct orb_del_model
 * @brief Service request to clear the model indicated in the platform
 * @version 0.8.0
 * @note data type passed back is an `bool`
 */
struct orb_del_model
: public http_request, 
  public cloud_base<bool>
{
    using callback = std::function<void(bool)>;
    static const std::string uri;

    /// @brief Constructor using the model's name
    /// @param model is the name of the model which is going to be deleted
    orb_del_model(const std::string model);
};

/**
 * @struct orb_query
 * @brief Service request to do a query image to detect objects
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
     * @brief Constructor using an image, a model
     *        and a threshold
     * @param image will be used to find the model indicated. @see noos::object::picture
     * @param model is the name of the model 
     *        which is going to be loaded. 
     * @param threshold is the minimum distance between 
     *        keypoints
     * @warning the model needs to be added in the platform before call this service.
     */
    orb_query(noos::object::picture image,
              const std::string model,
              const float threshold);

    /**
     * @brief Constructor without image for using it
     *        with vision_batch
     * @param model is the name of the model which the algorithm
     *        is going to look for in the image.          
     * @param threshold is the minimun distance between 
     *         keypoints 
     * @warning the model needs to be added in the platform before call this service.
     */
    orb_query(const std::string model,
              const float threshold);
};

}
}
#endif
