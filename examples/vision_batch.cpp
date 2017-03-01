/**
 * Copyright 2016 Ortelio
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
#include <rapp/cloud/service_controller.hpp>
#include <rapp/cloud/vision_batch.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/cloud/vision_recognition.hpp>
#include <rapp/objects/picture.hpp>
#include <iostream>

/**
 * @brief example to detect faces in a picture
 */
int main()
{
    /**
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    rapp::cloud::platform info = {"localhost", "8080", "mysecret", "alex"}; 
    rapp::cloud::service_controller ctrl(info);

    /**
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = rapp::object::picture("data/object_classes_picture_1.png");

    /**
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of rapp::object::face and
     * we show the size of the vector to know how many faces have 
     * been found.
     */
    auto face_callback = [&](std::vector<rapp::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    auto qr_callback = [&](std::vector<rapp::object::qr_code> qrs) { 
        std::cout << "Found " << qrs.size() << " qrs!" << std::endl;
    };

    rapp::cloud::vision_batch vision_services(pic);
    vision_services.insert_service<rapp::cloud::face_detection>(true, face_callback); 
    vision_services.insert_service<rapp::cloud::qr_recognition>(qr_callback); 
    vision_services.end();

    /**
     * We make a call to vision batch with face_detection and qr_detection
     * services with the same image.
     * For more information \see rapp::cloud::vision_batch
     */
    ctrl.make_call<rapp::cloud::vision_batch>(std::move(vision_services)); 
    //TODO: If this works do a method to return the name of the service instead of doing this
    //      A lot of possible errors.
    //std::vector<std::string> services_names = {"face_detection", "qr_detection"};
    //rapp::cloud::vision_batch vision_services(  pic,
    //                                            rapp::cloud::face_detection(false, face_callback),
    //                                            rapp::cloud::qr_recognition(qr_callback));

    //ctrl.make_call<rapp::cloud::vision_batch>(pic,
    //                                          //services_names,
    //                                          rapp::cloud::face_detection(false, face_callback),
    //                                          rapp::cloud::qr_recognition(qr_callback));
    return 0;
}
