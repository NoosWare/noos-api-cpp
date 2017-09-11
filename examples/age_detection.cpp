#include <noos/noos>
#include <iostream>
/*
 * @brief Example which recognises the age of a person
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from the filename into a picture class.
     * This particular image is of a young girl, so the result should reflect that.
     */
    auto pic = noos::object::picture("data/object_classes_picture_8.jpg");
    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * It will receive a vector of pairs, where the `first` is the label (string)
     * and the `second` is the assigned probability (float)
     */
    auto callback = [&](std::vector<std::pair<std::string,float>> arg) {
        for (const auto & pair : arg) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    };
    /*
     * We make a callable object using `age_detection` as the template parameter
     * and construct the callable data in one go.
     * @see noos::cloud::age_detection
     */
    callable<age_detection> cb(age_detection(pic), callback);
    cb.send();
    return 0;
}
