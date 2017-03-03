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
#include <rapp/objects/face.hpp>
#include <rapp/objects/picture.hpp>
#include <rapp/objects/human.hpp>
#include <rapp/objects/point.hpp>
#include <rapp/objects/orb_object.hpp>
#include <rapp/cloud/asio/http_request.hpp>
#include <rapp/cloud/cloud_base.hpp>
#include <rapp/cloud/deserialize.hpp>
namespace rapp 
{
namespace cloud 
{

/**
 * \class face_detection
 * \brief Asynchronous Service which will request the cloud to detect faces
 * \version 0.7.3
 * \date February 2017
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class face_detection 
: public http_request, 
  public cloud_base<face_detection,std::vector<rapp::object::face>>
{
public:
    // 
    typedef std::function<void(std::vector<rapp::object::face>)> callback;
    /**
     * \brief constructor
     * \param image is the input image \see rapp::object::picture
     * \param fast defines if this will be a fast call or not.
     * \param callback is the function that will receive a vector of detected face(s) 
     */
    face_detection(
                    const rapp::object::picture & image,
                    bool fast,
                    callback delegate
                  );
    /**
     * \brief construct without an image - part of a vision batch
     * \param boost defines if this is an optimised fast call
     * \param callback is the functor called when cloud replies
     */
    face_detection(
                    bool fast,
                    callback delegate
                  );

	/// \brief handle the rapp-platform JSON reply for single call - TODO @DEPRECATE
    void deserialise(std::string json) const;

    /// \return parameters of the class in json format
    std::string make_parameters() const;

    /// name of service (header)
    static const std::string uri;

private:
    bool fast_ = true;
    /// The callback called upon completion of receiving the detected faces
    callback delegate_;
};

/**
 * \class door_angle_detection
 * \brief detect open doors
 * \version 0.7.3
 * \date February 2017
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class door_angle_detection 
: public http_request, 
  public cloud_base<door_angle_detection,double>
{
public:
    // 
    typedef std::function<void(double door_angle)> callback;

    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive a number with the angle of the door
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    door_angle_detection(
                          const rapp::object::picture & image,
                          callback delegate
                        );
    
    /**
     * \brief Constructor without image
     * \param callback will receive the angle of the door
     */
    door_angle_detection(callback delegate);

	/// \brief handle the rapp-platform JSON reply for a single call - TODO @DEPRECATE
    void deserialise(std::string json) const;

    /// \return parameters in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

private:
    /// The callback called upon completion of receiving the detected faces
    callback delegate_;
};
/**
 * \class light_detection 
 * \brief detect the level of light
 * \version 0.7.0
 * \date September 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class light_detection 
: public http_request, 
  public cloud_base<light_detection,int>
{
public:
    // 
    typedef std::function<void(int light_level)> callback;

    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive the luminosity    
    */
    light_detection(
                     const rapp::object::picture & image,
                     callback delegate
                   );
    
    /**
     * \brief Constructor
     * \param callback will receive the luminosity
     */
    light_detection(callback delegate);

	/// \brief handle the rapp-platform JSON reply for a single call
    void deserialise(std::string json) const;

    /// \return parameters of the class in json format - TODO @DEPRECATE
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

private:
    /// The callback called upon completion of receiving the detected faces
    callback delegate_;
};

/**
 * \class human_detection
 * \brief detect humans in an image
 * \version 0.7.0
 * \date September 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class human_detection 
: public http_request, 
  public cloud_base<human_detection,std::vector<rapp::object::human>>
{
public:
    // 
    typedef std::function<void(std::vector<rapp::object::human>)> callback;
    /**
    * \brief Constructor
    * \param image is a picture object pointer
    * \param callback is the function that will receive the coordinates of a square which contain a human
    * \param image_format must be defined, e.g.: jpeg, png, gif, etc.
    */
    human_detection(
                      const rapp::object::picture & image,
                      callback delegate
                    );

    /**
     * \brief Constructor without image
     * \param callback will receive the coordinates of a square which contain a human
     */
    human_detection(callback delegate);

	/// \brief handle the rapp-platform JSON reply a single call - TODO @DEPRECATE
    void deserialise(std::string json) const;
    
    /// \return parameters of the class in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

private:
    /// The callback called upon completion of receiving the detected faces
    callback delegate_;
};

/**
 * \class object_detection_learn_object
 * \brief learn object gives by the user
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_learn_object 
: public http_request, 
  public cloud_base<object_detection_learn_object,int>
{
public:
    // 
    typedef std::function<void(int)> callback;
    /**
    * \brief Constructor
    * \param fname is the path (id) of model image
    * \param user is the user name
    * \param name is the name of the object
    * \param callback is the function that will receive an int with the result 
    */
    object_detection_learn_object(
                                   const rapp::object::picture & image,
                                   const std::string name,
                                   const std::string user,
                                   callback delegate
                                 );
    /**
     * \brief Constructor without image
     * \param name is the name of the object
     * \param user is the user name
     * \param callback will receive an int with the result
     */
    object_detection_learn_object(
                                   const std::string name,
                                   const std::string user,
                                   callback delegate
                                 );

	/// \brief handle the rapp-platform JSON reply - TODO: @DEPERCATE
    void deserialise(std::string json) const;

	/// \return paramenters in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

private:
    /// parameter name
    std::string name__;
    /// parameter user
    std::string user__;
public:
    /// callback
    callback delegate_;
};

/**
 * \class object_detection_clear_models
 * \brief Clears operational memory for selected user
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_clear_models 
: public http_request, 
  public cloud_base<object_detection_clear_models,int>
{
public:
    // 
    typedef std::function<void(int)> callback;
    /**
    * \brief Constructor
    * \param user is the user name
    * \param callback is the function that will receive an int 
    */
    object_detection_clear_models(
                                    const std::string user,
                                    callback delegate
                                 );
    
    /// \brief handle the rapp-platform JSON reply
    void deserialise(std::string json) const;

    /// name of service
    static const std::string uri;

//private:
    callback delegate_;
};

/**
 * \class object_detection_load_models
 * \brief Load one or more models to operational memory
 * \version 0.7.0
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_load_models 
: public http_request, 
  public cloud_base<object_detection_load_models,int>
{
public:
    // 
    typedef std::function<void(int)> callback;
    /**
    * \brief Constructor
    * \param user is the user name
    * \param names is the object names to load
    * \param callback is the function that will receive a string
    */
    object_detection_load_models(
                                  const std::string user,
                                  const std::vector<std::string> names,
                                  callback delegate
                                );
    
	/// \brief handle the rapp-platform JSON reply - TODO @DEPRECATE
    void deserialise(std::string json) const;

    /// name of service
    static const std::string uri;

//private:
    callback delegate_;
};

/**
 * \class object_detection_find_objects
 * \brief user can provide query image to detect objects
 * \version 0.7.2
 * \date October 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class object_detection_find_objects 
: public http_request, 
  public cloud_base<object_detection_find_objects,rapp::object::orb_object>
{
public:
    typedef std::function<void(rapp::object::orb_object)> callback;
    /**
    * \brief Constructor
    * \param fname is the path (id) of query image
    * \param user is the user name
    * \param limit is the limit search to N best matches
    * \param callback is the function that will receive the objects found
    */
    object_detection_find_objects(
                                  const rapp::object::picture & image,
                                  const std::string user,
                                  const int limit,
                                  callback delegate
                                );
    
    /**
     * \brief Constructor without image
     * \param user is the user name
     * \param limit is the limit search to N best matches
     * \param callback will receive the object found
     */
    object_detection_find_objects(
                                   const std::string user,
                                   const int limit,
                                   callback delegate
                                 );

	/// \brief handle the rapp-platform JSON reply for a single call
    void deserialise(std::string json) const;

    /// \return parameters of the class in json format
    std::string make_parameters() const;

    /// name of service
    static const std::string uri;

private:
    ///parameters user
    std::string user__;
    ///parameters limit
    int limit__;
public:
    /// delegate
    callback delegate_;
};

}
}
#endif
