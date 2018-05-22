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
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
    // 
    // We make a callable object of object_recognition class to recognise objects in the file
    // and we send it to the platform.
    // For more information @see noos::cloud::object_recognition
    // 
    callable<object_recognition,false> query(callback, node, pic);
    query.send();
    return 0;
}
