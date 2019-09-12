#include <noos/noos>
#include <iostream>

#if HAVE_OPENCV
#include <noos/misc/opencv.hpp>
#endif
// 
// Example to detect all objects in a file
// 
int main()
{
    using namespace noos::cloud;
    // 
    // A simple QR image
    //     
    std::string filename = "data/object_classes_picture_4.jpg";
    auto pic = noos::object::picture(filename);

#if HAVE_OPENCV
    auto mat = cv::imread(filename);
#endif
    // 
    // This lambda will receive a vector of possible QR codes detected.
    // It will then iterate and print for each one the associated "message".
    // 
    auto callback = [&](std::vector<noos::object::object> objs) {
        std::cout << "Objs: " <<objs.size() << std::endl;
        for (const auto obj: objs) {
            std::cout << obj.label<< std::endl;
            std::cout << obj.confidence << std::endl;
#if HAVE_OPENCV
            cv::rectangle(mat, cv::Point(obj.top_left_x, obj.top_left_y), 
                               cv::Point(obj.bottom_right_x, obj.bottom_right_y), cv::Scalar(0, 0, 255));
            cv::putText(mat, obj.label, cv::Point(obj.top_left_x, obj.top_left_y), 
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0));
#endif
        }
#if HAVE_OPENCV
        cv::imwrite("result.png", mat);
#endif

    };
    //
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    //platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
    platform node = {"localhost", "9001", "test_token", "test"};
    // 
    // We make a callable object of qr_recognition class to detect qr_codes in the file
    // and we send the information to the platform.
    // For more information @see noos::cloud::qr_recognition
    // 
    callable<object_detection,false, asio_http> query(callback, node, pic);
    query.send();
    return 0;
}
