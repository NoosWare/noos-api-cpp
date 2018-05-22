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

    //
    // We need to create a platform object with our user and password for using 
    // the NOOS Cloud 
    // IMPORTANT: You have to change your user and password. The example doesn't work
    //
    platform node = {"demo.noos.cloud", "9001", "your_pass", "your_user"};

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
    callable<orb_add_model,false> callable_learn(
            [](bool result) {
                std::cout << "learnt: " << std::boolalpha << result << std::endl;
            }, node, pic, "cat.jpg");
    callable_learn.send();

    /*
     * We make another callable object, now of orb_query to look
     * for the images learnt previously in the new image.
     */
    callable<orb_query,false> callable_find(find_cb, node, pic, "cat.jpg", 200);
    callable_find.send();

    /*
     * Finally, we create the last callable object, in this case of orb_del_models
     * class to clear the memory.
     */
    callable<orb_del_model,false>
    callable_clear(
            [](bool result){
                std::cout << "cleared: " << result << std::endl;
            }, node, "cat.jpg");
    callable_clear.send();
    return 0;
}
