#ifndef NOOS_CLOUD_VISION_RECOGNITION
#define NOOS_CLOUD_VISION_RECOGNITION
/**
 * LISENSE HERE
 */
#include "includes.ihh"
#include <noos/objects.hpp>
#include <noos/cloud/asio/http_request.hpp>
#include <noos/cloud/cloud_base.hpp>
#include <noos/cloud/vision_base.hpp>
namespace noos {
namespace cloud {
/**
 * @struct object_recognition
 * @brief Recognize an object from an image
 * @version 0.8.0
 * @date 06.09.2017
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @note data type passed back is `std::vector<std::pair<std::string,float>>`
 */
struct object_recognition 
: public http_request, 
  public cloud_base<std::vector<std::pair<std::string,float>>>,
  public vision_base
{
    using callback = std::function<void(data_type)>; 
    static const std::string uri;

    /// @brief Constructor taking an image
    /// @param image is a picture object reference @see noos::object::picture
    object_recognition(noos::object::picture image);

    /// @brief Empty ctor used by vision_batch
    object_recognition();
};

/**
 * @struct face_expression
 * @brief Recognise facial expressions from a person's image
 * @version 0.8.0
 * @date 06.09.2017
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @note data type passed back is `std::vector<std::pair<std::string,float>>`
 */
struct face_expression
: public http_request, 
  public cloud_base<std::vector<std::pair<std::string,float>>>,
  public vision_base
{
    using callback = std::function<void(data_type)>; 
    static const std::string uri;

    /// @brief Constructor taking an image
    /// @param image is a picture object reference @see noos::object::picture
    /// @warning For this service, the face of the image has to be already cropped.
    ///          Otherwise, the result will be random.
    face_expression(noos::object::picture image);

    /// @brief Empty ctor used by vision_batch
    face_expression();
};

/**
 * @struct qr_recognition
 * @brief Service request to detect QR codes
 * @version 0.7.0
 * @note data type passed back is `std::vector<noos::object::qr_code>`
 */
struct qr_recognition 
: public http_request, 
  public cloud_base<std::vector<noos::object::qr_code>>,
  public vision_base
{
    using callback = std::function<void(std::vector<noos::object::qr_code>)>;
    static const std::string uri;

    /// @brief Constructor taking an image
    /// @param image is a picture object reference @see noos::object::picture
    qr_recognition(noos::object::picture image);

    /// @brief Empty ctor used by vision_batch
    qr_recognition();
};

/**
 * @struct face_recognition
 * @brief Service request to recognise a person from a face picture
 * @version 0.8.0
 * @date 13.09.2017
 * @note data type passed back is `std::vector<noos::object::person>`
 */
struct face_recognition 
: public http_request, 
  public cloud_base<std::vector<noos::object::person>>,
  public vision_base
{
    using callback = std::function<void(std::vector<noos::object::person>)>;
    static const std::string uri;

    /// @brief Constructor taking an image
    /// @param image is a picture object reference @see noos::object::picture
    /// @warning the face mustn't be cropped. The platform will do it automatically.
    face_recognition(noos::object::picture image);

    /// @brief Empty ctor used by vision_batch
    face_recognition();
};
}
}
#endif
