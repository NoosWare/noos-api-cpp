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
     * We make a callable object of face_detection class 
     * and send the information to the platform to detect faces 
     * in the file.
     * For more information @see noos::cloud::face_detection
     */
    callable<face_detection,false> 
        callable_face(pic, 
                      [&](std::vector<noos::object::face> faces) { 
                            std::cout << "faced detected: " << faces.size() << std::endl;
                      });
    callable_face.send();
    return 0;
}
