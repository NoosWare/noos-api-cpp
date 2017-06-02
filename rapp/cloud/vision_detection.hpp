#ifndef RAPP_CLOUD_DETECTION
#define RAPP_CLOUD_DETECTION
#include "includes.ihh"
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
#include <rapp/objects.hpp>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/cloud.hpp>
namespace rapp {
namespace cloud {
/**
 * \struct face_detection
 * \brief Asynchronous Service which will request the cloud to detect faces
 * \version 0.7.3
 * \date February 2017
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct face_detection 
: public http_request, 
  public cloud_base<std::vector<rapp::object::face>>
{
    using callback = std::function<void(data_type)>;

    /**
     * @brief constructor
     * @param image is the input image \see rapp::object::picture
     * @param fast defines if this will be a fast call or not.
     */
    face_detection(const rapp::object::picture & image, bool fast);
    
    /**
     * @brief construct without an image - part of a vision batch
     * @param boost defines if this is an optimised fast call
     */
    face_detection(bool fast);

    /// @return parameters of the struct in json format
    std::string make_parameters() const;

    /// name of service (header)
    static const std::string uri;

    /// boolean for fast or slow processing
    bool fast = true;
};

/**
 * @struct light_detection 
 * @brief detect the level of light
 * @version 0.7.3
 * @date 02.06.2017
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct light_detection 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;

    /**
     * @brief Construct using an image
     * @param image is a picture object pointer
     */
    light_detection(const rapp::object::picture & image);
    
    /**
      * @brief Constructor
      * @param callback will receive the luminosity
      */
    light_detection();

    /// @return parameters of the struct in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;
};

/**
 * @struct human_detection
 * @brief detect humans in an image
 * @version 0.7.3
 * @date 02.06.2017
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct human_detection 
: public http_request, 
  public cloud_base<std::vector<rapp::object::human>>
{
    using callback = std::function<void(data_type)>;

    /**
     * @brief Constructor
     * @param image is a picture object pointer
     * @param callback is the function that will receive the coordinates of a square which contain a human
     * @param image_format must be defined, e.g.: jpeg, png, gif, etc.
     */
    human_detection(const rapp::object::picture & image);

    /**
     * @brief Constructor without image
     */
    human_detection();

    /// \return parameters of the struct in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;
};

/**
 * @struct orb_learn_object
 * @brief learn object gives by the user
 * @version 0.7.3
 * @date 02.06.2017
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct orb_learn_object 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;

    /**
     * @brief Constructor
     * @param fname is the path (id) of model image
     * @param user is the user name
     * @param name is the name of the object
     */
    orb_learn_object(
                       const rapp::object::picture & image,
                       const std::string name,
                       const std::string user,
                     );
    /**
     * @brief Constructor without image
     * @param name is the name of the object
     * @param user is the user name
     */
    orb_learn_object(
                       const std::string name,
                       const std::string user
                    );

	/// @return paramenters in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

    /// parameter name
    std::string name;
    /// parameter user
    std::string user;
};

/**
 * @struct orb_clear_models
 * @brief Clears operational memory for selected user
 * @version 0.7.3
 * @date October 2016
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct orb_clear_models 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;

    /**
     * @brief Constructor
     * @param user is the user name
     * @param callback is the function that will receive an int 
     */
    orb_clear_models(const std::string user);
    
    /// name of service
    static const std::string uri;
};

/**
 * @struct object_detection_load_models
 * @brief Load one or more models to operational memory
 * @version 0.7.3
 * @date October 2016
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct orb_load_models 
: public http_request, 
  public cloud_base<int>
{
    using callback = std::function<void(int)>;

    /**
    * @brief Constructor
    * @param user is the user name
    * @param names is the object names to load
    */
    orb_load_models(
                      const std::string user,
                      const std::vector<std::string> names
                    );
    
    /// name of service
    static const std::string uri;
};

/**
 * @struct object_detection_find_objects
 * @brief user can provide query image to detect objects
 * @version 0.7.2
 * @date October 2016
 * @author Maria Ramos <m.ramos@ortelio.co.uk>
 */
struct orb_find_objects 
: public http_request, 
  public cloud_base<rapp::object::orb_object>
{
    using callback = std::function<void(rapp::object::orb_object)>;

    /**
     * @brief Constructor
     * @param fname is the path (id) of query image
     * @param user is the user name
     * @param limit is the limit search to N best matches
     */
    orb_find_objects(
                      const rapp::object::picture & image,
                      const std::string user,
                      const int limit
                    );
    
    /**
     * @brief Constructor without image
     * @param user is the user name
     * @param limit is the limit search to N best matches
     * @param callback will receive the object found
     */
    orb_find_objects(
                       const std::string user,
                       const int limit
                     );

    /// \return parameters of the struct in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

    ///parameters user
    std::string user;
    ///parameters limit
    int limit;
};

}
}
#endif
