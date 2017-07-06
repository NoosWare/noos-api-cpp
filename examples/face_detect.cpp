#include <noos/noos>
#include <iostream>
/*
 * @brief example to detect faces in a picture
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = noos::object::picture("data/object_classes_picture_1.png");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::face and
     * we show the size of the vector to know how many faces have 
     * been found.
     */
    auto face_request = face_detection(pic);
    auto callback = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    /*
     * We make a call to face_detection class to detect faces in the file
     * For more information \see noos::cloud::face_detection
     */
    callable<face_detection,false>cb(face_request, callback);
    cb.send();
    return 0;
}
