#ifndef CLOUD_VISION_RECOGNITION
#define CLOUD_VISION_RECOGNITION
/**
 * LISENSE HERE
 *
 * @version 0.7.3
 * @date 7 June 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
#include "includes.ihh"
#include <rapp/objects.hpp>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/cloud.hpp>

namespace rapp {
namespace cloud {
/**
 * @struct object_recognition
 * @brief recognize object from an image
 */
struct object_recognition 
: public http_request, 
  public cloud_base<std::string>
{
    using callback = std::function<void(std::string)>; 
    static const std::string uri;

    /// @param image is a picture object pointer
    object_recognition(const rapp::object::picture & image);

    /// @brief empty ctor used by vision batch
    object_recognition();
};

/**
 * @struct qr_recognition
 * @brief service request to detect QR codes
 */
struct qr_recognition 
: public http_request, 
  public cloud_base<std::vector<rapp::object::qr_code>>
{
    using callback = std::function<void(std::vector<rapp::object::qr_code>)>;
    static const std::string uri;

    /// @param image is a picture object pointer
    qr_recognition(
                    const rapp::object::picture & image,
                    callback delegate
                  );
    
    /// @brief empty ctor used by vision batch
    qr_recognition(callback delegate);
};

}
}
#endif
