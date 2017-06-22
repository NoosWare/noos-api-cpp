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
 * @version 0.7.3
 * @date 7 June 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 *
 * WARNING: currently not supported by our platform!!!
 */
struct object_recognition 
: public http_request, 
  public cloud_base<std::string>,
  public vision_base
{
    using callback = std::function<void(std::string)>; 
    static const std::string uri;

    /// @param image is a picture object pointer
    object_recognition(const noos::object::picture & image);

    /// @brief empty ctor used by vision batch
    object_recognition();
};
/**
 * @struct qr_recognition
 * @brief service request to detect QR codes
 */
struct qr_recognition 
: public http_request, 
  public cloud_base<std::vector<noos::object::qr_code>>,
  public vision_base
{
    using callback = std::function<void(std::vector<noos::object::qr_code>)>;
    static const std::string uri;

    /// @param image is a picture object pointer
    qr_recognition(const noos::object::picture & image);

    /// @brief empty ctor used by vision batch
    qr_recognition();
};
}
}
#endif
