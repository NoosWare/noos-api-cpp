#include <noos/noos>
#include <iostream>
/*
 * \brief Example to recognise objects of a picture
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = noos::object::picture("data/object_classes_picture_5.jpg");
    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a string with the type of object that
     * it has been found.        
    */
    auto callback = [&](std::vector<std::pair<std::string,float>> objects) {
        if (objects.empty()) {
            std::cout << "No objects found" << std::endl;
        }
        else {
            for (const auto & pair : objects) {
                std::cout << pair.first << " " << pair.second << std::endl;
            }
        }
    };
    /*
     * We make a callable object of object_recognition class to recognise objects in the file
     * and we send it to the platform.
     * For more information \see noos::cloud::object_recognition
     */
    callable<object_recognition> callable_obj(object_recognition(pic), callback);
    callable_obj.send();
    return 0;
}
