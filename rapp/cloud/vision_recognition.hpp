#ifndef RAPP_CLOUD_RECOGNITION
#define RAPP_CLOUD_RECOGNITION
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "includes.ihh"
#include <rapp/objects.hpp>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/cloud.hpp>

namespace rapp 
{
namespace cloud 
{
/**
 * \struct object_recognition
 * \brief recognize object from an image
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct object_recognition 
: public http_request, 
  public cloud_base<object_recognition,std::string>
{
    typedef std::function<void(std::string)> callback; 
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a string
    */
    object_recognition(
                        const rapp::object::picture & image,
                        callback delegate
                      );
    /**
     * \brief Constructor without image
     * \param callback will receive a string 
     */
    object_recognition(callback delegate);

    /// \return parameters of the struct in json format
    std::string make_parameters() const;

    //name header http
    static const std::string uri;

    //callback 
    const callback delegate;

};

/**
 * \struct qr_recognition
 * \brief service request to detect QR codes
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct qr_recognition 
: public http_request, 
  public cloud_base<qr_recognition,std::vector<rapp::object::qr_code>>
{
    typedef std::function<void(std::vector<rapp::object::qr_code>)> callback;
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a vector of detected qr(s)
    */
    qr_recognition(
                    const rapp::object::picture & image,
                    callback delegate
                  );

    /**
     * \brief Constructor without image
     * \param callback will receive a vector of detected qr(s)
     */
    qr_recognition(callback delegate);

    /// \return parameters of the struct in json format
    std::string make_parameters() const;

    //name header http
    static const std::string uri;

    /// The callback called upon completion of receiving the qr codes
    const callback delegate;
};

}
}
#endif
