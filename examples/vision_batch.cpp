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
#include <rapp/cloud.hpp>
#include <rapp/objects.hpp>
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
    auto face_cb = [&](std::vector<rapp::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    auto human_cb = [&](std::vector<rapp::object::human> humans) { 
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    using face_d   = rapp::cloud::face_detection;
    using human_d  = rapp::cloud::human_detection;
    using vision_b = rapp::cloud::vision_batch<face_d,human_d>;

    ctrl.make_call<vision_b>(pic,
                             face_d(false, face_cb),
                             human_d(human_cb));
    return 0;
}
