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
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive an int to indicate the state. 
    */
    auto callback = [](bool result) {
            std::cout << "Result: " << std::boolalpha << result << std::endl;
    };

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive the data of the objects found. 
    */
    auto find_cb = [](const std::vector<noos::object::point2d<float>> keypoints) 
    {
        std::cout << "Number of good keypoints: " << keypoints.size() << std::endl;
    };
    /*
     * We make a callable object of learn_object class to learn objects from the file
     * and send the information to the platform.
     * For more information \see noos::cloud::orb_learn_object
     */
    callable<orb_learn_object> callable_learn(orb_learn_object(pic, "cat.jpg"), callback);
    callable_learn.send();

    /*
     * We make another callable object, now of orb_find_objects to look
     * for the images learnt previously in the new image.
     * For more information \see noos::cloud::orb_find_objects
     */
    callable<orb_find_objects> callable_find(orb_find_objects(pic, "cat.jpg", 200), find_cb);
    callable_find.send();

    /*
     * Finally, we create the last callable object, in this case of orb_clear_models
     * class to clear the memory.
     * For more information \see noos::cloud::orb_clear_models
     */
    callable<orb_clear_model> callable_clear(orb_clear_model("cat.jpg"), callback);
    callable_clear.send();
    return 0;
}
