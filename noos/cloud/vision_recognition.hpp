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
 * @brief recognize object from an image
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

    /// @param image is a picture object reference
    object_recognition(noos::object::picture image);

    /// @brief empty ctor used by vision batch
    object_recognition();
};

/**
 * @struct face_expression
 * @brief recognise facial expressions from a person's image
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

    /// @param image is a picture 
    face_expression(noos::object::picture image);

    /// @brief empty ctor used by vision batch
    face_expression();
};

/**
 * @struct qr_recognition
 * @brief service request to detect QR codes
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

    /// @param image is a picture object
    qr_recognition(noos::object::picture image);

    /// @brief empty ctor used by vision batch
    qr_recognition();
};

/**
 * @struct face_recognition
 * @brief recognise faces
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

    /// @param image is a picture object
    face_recognition(noos::object::picture image);

    /// @brief empty ctor used by vision batch
    face_recognition();
};
}
}
#endif
