#include <noos/noos>
#include <iostream>
/*
 * \brief Example to detect qr in a file
 */
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */    
    auto pic = noos::object::picture("data/asio_classes_qr_code_1.png");
    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive a vector of noos::object::qr_code and
     * we show the size of the vector to know how many qr_codes have 
     * been found.
     */
    auto callback = [&](std::vector<noos::object::qr_code> codes) {
        std::cout << "QR: " << codes.size() << std::endl;
        for (const auto code : codes) {
            std::cout << code.message << std::endl;
        }
    };
    /*
     * We make a callable object of qr_recognition class to detect qr_codes in the file
     * and we send the information to the platform.
     * For more information \see noos::cloud::qr_recognition
     */
    auto query = make<qr_recognition>(callback, pic);
    query.send();
    return 0;
} 
