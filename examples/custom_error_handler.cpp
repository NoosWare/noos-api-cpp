#include <noos/noos>
#include <iostream>
// 
// Example to create a custom error handler
// 

/*
 * A new struct to handle the errors about communication
 * with the platform
 */
struct my_error_handler
{
    /* This method is compulsory. It will manage the errors */
    void operator()(boost::system::error_code & error) const
    {
        if (error.value() != 0) {
            std::cout << "Error value: " << error.value() <<
                        " Error message: " << error.message() << std::endl; 
        }
        else {
            std::cout << "Success" << std::endl;
        }
    }
};

int main()
{
    using namespace noos::cloud;
    // 
    // An image is loaded from a PNG on disk.
    // 
    auto pic = noos::object::picture("data/object_classes_picture_1.png");
    // 
    // We make a callable object of face_detection class 
    // and send the query to the platform to detect faces 
    // For more information @see noos::cloud::face_detection
    // In this example, we use an inline lambda which will print
    // the coordinates of detected faces.
    //      
    auto callback = [&](std::vector<noos::object::face> faces) { 
                        std::cout << "faced detected: " << faces.size() << std::endl;
                    };
    //
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
 
    //
    // For adding our error handler, we have to specify all the template parameters
    // that callable class needs. For more information @see noos::cloud::callable
    //
    callable<face_detection,
             false,
             asio_http,
             my_error_handler> query(callback, 
                                     node, 
                                     pic);

    query.send(1);
    return 0;
}
