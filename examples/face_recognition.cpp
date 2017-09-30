#include <noos/noos>
#include <iostream>
// 
// Example to detect faces in a picture
// 
int main()
{
    using namespace noos::cloud;
    // 
    // The image is loaded from disk.
    // 
    auto pic = noos::object::picture("data/object_classes_picture_1.png");
    // 
    // The callback lambda will receive a vector of noos::object::face and
    // we show the size of the vector to know how many faces have 
    // been found.
    // 
    auto callback = [&](std::vector<noos::object::person> faces) { 
        if (faces.size() > 0) { 
            for (auto face : faces) {
                // Coordinates?
                std::cout << "Label: " <<face.label << std::endl;
                std::cout << "Name: " <<face.name << std::endl;
                std::cout << "Confidence: " << face.confidence << std::endl; 
            }
        }
        else {
            std::cout << "didn't recognise anyone!" << std::endl;
        }
    };
    // 
    // We make a callable object of face_detection class 
    // and send the information to the platform to detect faces 
    // in the file.
    // For more information @see noos::cloud::face_detection
    // 
    auto query = call<face_recognition,false>(callback, pic);
    query.send();
    return 0;
}
