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
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
    // 
    // We make a callable object of human_detection class and we send
    // the information to the platform to detect humans in the file.
    // The reply will be processed by the lambda callback, and the connection
    // will be closed upon completion
    //
    // For more information @see noos::cloud::human_detection
    // 
	callable<human_detection,false> 
	query([&](std::vector<noos::object::human> humans) {
                    std::cout << "Found " << humans.size() << " humans!" << std::endl;
          }, node, pic);
    query.send();

    return 0;
}
