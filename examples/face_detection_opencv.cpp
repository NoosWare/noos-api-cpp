#include <noos/noos>
#include <iostream>

#if HAVE_OPENCV

#include "noos/misc/opencv.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#endif

// 
// Example to detect faces in a picture
// using OPENCV
// 
int main()
{
    //This special `if` is only required in this library, to allow use and not use opencv.
    //You don't have to use it in your program 
#if (HAVE_OPENCV)
    using namespace noos::cloud;
    // 
    // An image is loaded from a PNG on disk.
    // 
    cv::Mat pic = cv::imread("data/object_classes_picture_1.png");
    // 
    // We make a callable object of face_detection class 
    // and send the query to the platform to detect faces 
    // For more information @see noos::cloud::face_detection
    // In this example, we use an inline lambda which will print
    // the coordinates of detected faces.
    // We also specify that we won't keep alive the connection, using `false`
    // as the second template parameter.
    // 
    auto callback = [&](std::vector<noos::object::face> faces) { 
                        std::cout << "faced detected: " << faces.size() << std::endl;
                    };
    //
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "test_token", "test"};
 
    //callable requires noos::object::picture but we have a cv::Mat. The solution is 
    //calling the function `noos::misc::mat_to_pict`. It will do the job for us.
    callable<face_detection, false> query(callback, node, noos::misc::mat_to_pict(pic));
    query.send();
#else
    throw std::runtime_error("Compile the library with the option -DUSE_OPENCV=ON to run this example");
#endif
    return 0;
}
