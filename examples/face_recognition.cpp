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
    auto face_request = face_recognition(pic);
    auto callback = [&](std::vector<noos::object::face_recognition_obj> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
        if (faces.size() > 0) { 
            for (auto face : faces) {
                std::cout << "Label: " <<face.label << std::endl;
                std::cout << "Confidence: " << face.confidence << std::endl; 
            }
        }
    };

    /*
     * We make a callable object of face_detection class 
     * and send the information to the platform to detect faces 
     * in the file.
     * For more information \see noos::cloud::face_detection
     */
    callable<face_recognition,false>callable(face_request, callback);
    callable.send();
    return 0;
}
