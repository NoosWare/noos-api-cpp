#include <noos/noos>
#include <iostream>
/*
 * \brief example to do a cloud batch 
 */
int main()
{
    /*
     * The image is loaded from its path to a picture class.
     * More than one image can be load to do the example. In this case
     * we use the same image to detect everything.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = noos::object::picture("data/object_classes_picture_7.jpg");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::face and
     * we show the size of the vector to know how many faces have 
     * been found.
     */
    auto face_cb = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };

    /*
     * A lambda is needed for each class that we have.
     * This one receive a vector of noos::object::human and
     * we show the size of the vector to know how many humans have 
     * been found.
     */
    auto human_cb = [&](std::vector<noos::object::human> humans) {
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    /*
     * We make the calls to face_detection, human_detection and
     * door_angle_detection classes
     * For more information \see noos::cloud::face_detection
     *                      \see noos::cloud::human_detection
     */
    ctrl.make_calls(noos::cloud::face_detection(pic, false, face_cb),
                    noos::cloud::human_detection(pic, human_cb));
    return 0;
}
