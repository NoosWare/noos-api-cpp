#include <noos/noos>
#include <iostream>
/*
 * \brief Example to detect hazards in a picture 
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     * You can test no light with `object_classes_picture_4.jpg` file
     */
    auto pic = noos::object::picture("data/object_classes_picture_5.jpg");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a double and we show the angle of the door
     * in the case that a hazard is found.         
     */
    auto callback = [&](int light_level) {
        std::cout << "Light level: " << light_level  << std::endl;
    };

    /*
     * We make a callable object of light_detection class to detect 
     * the level of light in the file. 
     * Then we send the information to the platform.
     * For more information \see noos::cloud::light_detection
     */
    callable<light_detection,false> cb(light_detection(pic), callback);
    cb.send();

    return 0;
}
