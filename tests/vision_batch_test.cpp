#include <rapp/cloud/vision_recognition.hpp>
#include <rapp/cloud/vision_detection.hpp>
#include <rapp/cloud/vision_batch.hpp>

/**
 * @brief test to vision_batch
 */
int main() 
{
    //vision batch
    auto pic = rapp::object::picture("tests/data/asio_classes_qr_code_1.png");
    rapp::cloud::vision_batch vision_test(pic);

    //callbacks
    auto face_cb = [] (std::vector<rapp::object::face> faces) {
        std::cout << "Found: " << faces.size() << " faces" << std::endl;
    };
    auto qr_cb = [] (std::vector<rapp::object::qr_code> qr) {
        std::cout << "Found: " << qr.size() << " qrs" << std::endl;
    };

    //insert services
    vision_test.insert<rapp::cloud::face_detection>("face_detection", true, face_cb); 
    vision_test.insert<rapp::cloud::qr_recognition>("qr_recognition", qr_cb);
    vision_test.end();

    rapp::cloud::platform info = {"1", "8080", "mysecret", "blah"}; 
    boost::asio::streambuf request;
    vision_test.fill_buffer(boost::ref(request), info);

}
