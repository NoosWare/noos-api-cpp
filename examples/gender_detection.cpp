#include <noos/noos>
#include <iostream>
// 
// Example which recognises the gender of a person
// 
int main()
{
    using namespace noos::cloud;
    // 
    // The image is loaded from disk into a picture class.
    // This particular image is of a man, so the result should reflect that.
    // 
    auto pic = noos::object::picture("data/object_classes_picture_9.jpg");
    // 
    // This lambda will receive a vector of pairs, where the `first` is the label (string)
    // and the `second` is the assigned probability (float)
    // 
    auto callback = [&](std::vector<std::pair<std::string,float>> arg) {
        for (const auto & pair : arg) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    };
    // 
    // We make a callable object using `gender_detection` as the template parameter
    // and construct the callable data in one go.
    // @see noos::cloud::gender_detection
    // 
    auto query = call<gender_detection,false>(callback, pic);
    query.send();
    return 0;
}
