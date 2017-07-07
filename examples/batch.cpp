#include <noos/noos>
#include <iostream>
/*
 * \brief example to do a cloud batch 
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * More than one image can be load to do the example. In this case
     * we use the same image to detect everything.
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
    auto face_callback = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    /*
     * A lambda is needed for each class that we have.
     * This one receive a vector of noos::object::human and
     * we show the size of the vector to know how many humans have 
     * been found.
     */
    auto human_callback = [&](std::vector<noos::object::human> humans) {
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    /*
     * A callable is created per service
     */
    callable<face_detection, false> cb_face(face_detection(pic), face_callback);
    callable<human_detection, false> cb_human(human_detection(pic), human_callback);

    /*
     * We make the calls to face_detection and human_detection
     * For more information \see noos::cloud::face_detection
     *                      \see noos::cloud::human_detection
     */
    cb_face.send();
    cb_human.send();

    return 0;
}
