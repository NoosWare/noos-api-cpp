#include <noos/noos>
#include <iostream>
// 
// Example to recognise objects of a picture
// 
int main()
{
    using namespace noos::cloud;
    // 
    // An image of a light bulb
    // 
    auto pic = noos::object::picture("data/object_classes_picture_5.jpg");
    //
    // This lambda callback will receive the reply from the platform.
    // Each pair in the vector is a string (label) and the associated 
    // certainty or probability of the image containing that object label.  
    //
    auto callback = [&](std::vector<std::pair<std::string,float>> objects) {
        if (objects.empty()) {
            std::cout << "No objects found" << std::endl;
        }
        for (const auto & pair : objects) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    };
    // 
    // We make a callable object of object_recognition class to recognise objects in the file
    // and we send it to the platform.
    // For more information @see noos::cloud::object_recognition
    // 
    auto query = call<object_recognition,false>(callback, pic);
    query.send();
    return 0;
}
