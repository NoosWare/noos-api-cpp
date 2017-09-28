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
    auto callback = [](int result) {
        switch (result) {
            case 0:
                std::cout << "Correct" << std::endl;
                break;
            case -1:
                std::cout << "No models" << std::endl;
                break;
            case -2:
                std::cout << "No image to analyse" << std::endl;
                break;
            default:
                std::cout << "Error" <<std::endl;
                break;
        }
    };

    /*
     * Construct a lambda, std::function or bind your own functor.
     * In this example we'll pass an inline lambda as the callback.
     * All it does is receive the data of the objects found. 
    */
    auto find_cb = [](const noos::object::orb_object obj) 
    {
        std::cout << "Number of objects found: " << obj.names.size() << std::endl;
        std::cout << "Size vector points: " << obj.points.size() << std::endl;
        std::cout << "Size of scores: " << obj.scores.size() << std::endl;
        std::cout << "Result: " << obj.result << std::endl; 
    };
    /*
     * We make a callable object of learn_object class to learn objects from the file
     * and send the information to the platform.
     * For more information \see noos::cloud::orb_learn_object
     */
    callable<orb_learn_object> callable_learn(orb_learn_object(pic, "cat"), callback);
    callable_learn.send();

    /*
     * Before finding objects, we load them beforehand.
     * In this vector we say the names of the objects to load
     */
    std::vector<std::string> names = {"cat"};

    /*
     * We make another callable object,in this case of load_models class to 
     * load objects from the file
     * For more information \see noos::cloud::object_detection_load_models
     */
    callable<orb_load_models> callable_load(orb_load_models(names), callback);
    callable_load.send();

    /*
     * We make another callable object, now of orb_find_objects to look
     * for the images learnt previously in the new image.
     * For more information \see noos::cloud::orb_find_objects
     */
    callable<orb_find_objects> callable_find(orb_find_objects(pic, 1), find_cb);
    callable_find.send();

    /*
     * Finally, we create the last callable object, in this case of orb_clear_models
     * class to clear the memory.
     * For more information \see noos::cloud::orb_clear_models
     */
    callable<orb_clear_models> callable_clear(orb_clear_models("noos"), callback);
    callable_clear.send();
    return 0;
}
