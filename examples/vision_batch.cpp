#include <noos/noos>
// 
// Example of a vision batch,
// which detects faces and humans in a picture
// 
int main()
{
    using namespace noos::cloud;
    //
    // An image is loaded from disk
    //
    auto pic = noos::object::picture("data/object_classes_picture_1.png");
    //
    // This lambda will print the amount of detected faces
    //
    auto face_cb = [&](std::vector<noos::object::face> faces) { 
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    };
    //
    // This lambda will print the amount of detected human bodies
    //
    auto human_cb = [&](std::vector<noos::object::human> humans) { 
        std::cout << "Found " << humans.size() << " humans!" << std::endl;
    };
    //
    // we alias the `vision_batch` template arguments.
    // NOTE: vision_batch ties a `cloud_type` (e.g., face_detection or human_detection)
    //       to a callback.
    //       Therefore you have to wrap them using `tied` (or `make_tie`) in order
    //       to identify which callback belongs to which cloud query.
    //       In this instance, we tie `face_detection` to the `face_cb` lambda,
    //       and similarly, we tie `human_detection` to the `human_cb` lambda.
    //
    using vbatch = vision_batch<tied<face_detection>,tied<human_detection>>;
    callable<vbatch> query(pic,
                           default_node,
                           tied<face_detection>(face_cb), 
                           tied<human_detection>(human_cb));

    //
    // we increate the time-out to 3 seconds on purpose.
    //
    query.send(3);
    return 0;
}
