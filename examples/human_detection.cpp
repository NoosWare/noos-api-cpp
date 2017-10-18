#include <noos/noos>
#include <iostream>
// 
// Example to detect humans in a image 
// 
int main()
{
    using namespace noos::cloud;
    //
    // A picture with humans
    //
    auto pic = noos::object::picture("data/object_classes_picture_7.jpg");
    // 
    // We make a callable object of human_detection class and we send
    // the information to the platform to detect humans in the file.
    // The reply will be processed by the lambda callback, and the connection
    // will be closed upon completion
    //
    // For more information @see noos::cloud::human_detection
    // 
    auto query = call<human_detection,false>(
                 [&](std::vector<noos::object::human> humans) {
                    std::cout << "Found " << humans.size() << " humans!" << std::endl;
                 }, pic);
    query.send();
    return 0;
}
