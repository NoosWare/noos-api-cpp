#include <noos/noos>
#include <iostream>
// 
// Example to detect qr in a file
// 
int main()
{
    using namespace noos::cloud;
    // 
    // A simple QR image
    //     
    auto pic = noos::object::picture("data/asio_classes_qr_code_1.png");
    // 
    // This lambda will receive a vector of possible QR codes detected.
    // It will then iterate and print for each one the associated "message".
    // 
    auto callback = [&](std::vector<noos::object::qr_code> codes) {
        std::cout << "QR: " << codes.size() << std::endl;
        for (const auto code : codes) {
            std::cout << code.message << std::endl;
        }
    };
    //
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};
    // 
    // We make a callable object of qr_recognition class to detect qr_codes in the file
    // and we send the information to the platform.
    // For more information @see noos::cloud::qr_recognition
    // 
    callable<qr_recognition,false> query(callback, node, pic);
    query.send();
    return 0;
} 
