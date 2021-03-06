#include <noos/noos>
#include <iostream>
//
// Example which recognises the age of a person
//
int main()
{
    //
    // this is for convenience only
    //
    using namespace noos::cloud;
    // The image is loaded from the filename into a picture class.
    // This particular image is of a young girl, so the result should reflect that.
    auto pic = noos::object::picture("data/object_classes_picture_8.jpg");
    //
    // In this example we'll pass a lambda as the callback.
    // It will receive a vector of pairs, where the `first` is the label (string)
    // and the `second` is the assigned probability (float)
    //
    auto callback = [&](std::vector<std::pair<std::string,float>> arg) {
        for (const auto & pair : arg) {
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
    // We make a callable object using `age_detection` as the template parameter
    // of the helper method `call`. 
    // The second template parameter (false) specifies that we won't keep alive the connection
    // For ino on age detection @see noos::cloud::age_detection
    // 
    callable<age_detection,true> query(callback, node, pic);
    // we send the query - after we receive a reply at our callback, the connection will close.
    //
    query.send();

    return 0;
}
