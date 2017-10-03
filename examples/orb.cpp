#include <noos/noos>
#include <iostream>
// TODO: REMOVE AND PUT INTO THE ROS NODE STUFF
int main()
{
    using namespace noos::cloud;
    /*
     * The image is loaded from its path to a picture class.
     * If you run the example inside examples folder, this path is valid.
     * In other cases, you'll have to change it for a proper one.
     */
    auto pic = noos::object::picture("data/object_classes_picture_2.jpg");

    /*
     * Construct a lambda, std::function or bind your own functor.
     */
    auto find_cb = [](const std::vector<noos::object::point2d<float>> keypoints) {
        std::cout << "Number of good keypoints: " << keypoints.size() << std::endl;
    };
    /*
     * We make a callable object of learn_object class to learn objects from the file
     * and send the information to the platform.
     */
    auto callable_learn  = call<orb_learn_object,false>(
            [](bool result) {
                std::cout << "learnt: " << std::boolalpha << result << std::endl;
            }, pic, "cat.jpg");
    callable_learn.send();

    /*
     * We make another callable object, now of orb_find_objects to look
     * for the images learnt previously in the new image.
     */
    auto callable_find = call<orb_find_objects,false>(find_cb, pic, "cat.jpg", 200);
    callable_find.send();

    /*
     * Finally, we create the last callable object, in this case of orb_clear_models
     * class to clear the memory.
     */
    auto callable_clear = call<orb_clear_model,false>(
            [](bool result){
                std::cout << "cleared: " << result << std::endl;
            }, "cat.jpg");
    callable_clear.send();
    return 0;
}
