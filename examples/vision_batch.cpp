#include <noos/noos>
#include <iostream>
#include <tuple>

/**
 * @brief example to detect faces in a picture
 */
int main()
{
    using namespace noos::cloud;
    /**
     * Construct the platform info setting the hostname/IP, port and authentication token
     * Then proceed to create a cloud controller.
     * We'll use this object to create cloud calls to the platform.
     */
    platform info = {"localhost", "8080", "mysecret", "alex"}; 
    node<> ctrl(info);

    /**
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = noos::object::picture("data/object_classes_picture_1.png");

    /**
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::face and
     * we show the size of the vector to know how many faces have 
     * been found.
     */
    auto face_cb = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    auto human_cb = [&](std::vector<noos::object::human> humans) { 
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    //auto batch = noos::cloud::vision_batch<face_pair, human_pair>(std::make_pair(face_d(), face_cb), 
    //                                                              std::make_pair(human_d(), human_cb));

    //auto call = ctrl.make_one(batch, 
    //                          std::bind(vision_batch::process, &batch, std::placeholders::_1));

    auto call_obj = ctrl.make(pic, 
                              std::make_pair(face_detection(), face_cb), 
                              std::make_pair(human_detection(), human_cb));
    ctrl.call(call_obj);
    return 0;
}
