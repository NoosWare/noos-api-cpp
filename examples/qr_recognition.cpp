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
    // We make a callable object of qr_recognition class to detect qr_codes in the file
    // and we send the information to the platform.
    // For more information @see noos::cloud::qr_recognition
    // 
    auto query = call<qr_recognition,false>(callback, pic);
    //callable<qr_recognition, false> query(qr_recognition(pic), callback);
    query.send();
    return 0;
} 
