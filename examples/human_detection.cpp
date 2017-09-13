#include <noos/noos>
#include <iostream>
/*
 * \brief example to detect humans in a image 
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = noos::object::picture("data/object_classes_picture_7.png");

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::human and
     * we show the size of the vector to know how many humans have 
     * been found.
     */
    auto human_request = human_detection(pic);
    auto callback = [&](std::vector<noos::object::human> humans) {
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };

    /*
     * We make a callable object of human_detection class  and we send
     * the information to the platform to detect humans in the file.
     * For more information \see noos::cloud::human_detection
     */
    callable<noos::cloud::human_detection> callable_human(human_request, callback);
    callable_human.send();
    return 0;
}
