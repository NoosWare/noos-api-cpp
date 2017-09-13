#include <noos/noos>
#include <iostream>
#include <functional>

using namespace noos::cloud;

class reactor
{
public:
    /*
     * \brief constructor passing the information of the platform
     */
    reactor()
    :callable_obj_(default_node)
    {}

    /*
     * \brief method to see how many faces have been found
     */
    void handle_face(std::vector<noos::object::face> faces)
    {        
        std::cout << "Found " << faces.size() << " faces!" << std::endl;
    }

    /*
     * \brief method to make a call for face_detection
     * \param pic is the picture where we are going to look for a face
     */
    void run(noos::object::picture pic)
    {
        callable_obj_.object = face_detection(pic);
        callable_obj_.functor = std::bind(&reactor::handle_face, this, std::placeholders::_1);
        callable_obj_.send();
    }
    
private:
    callable<face_detection, true> callable_obj_;
};

/*
 * \brief example to show how the new class works
 */
int main()
{
    /* 
     * We load an image. You have to run thi example in the examples folder.
     * In other cases, use the proper path.
     */
    auto pict = noos::object::picture("data/object_classes_picture_1.png");

    /*
     * We initialize an reactor object.
     * We have to pass it like a pointer because its member `callable` can't be copied
     */
    auto my_reactor = std::make_unique<reactor>();

    /*
     * The method run is done to make the call to the platform,
     * passing the corresponding parameters.
     */
    my_reactor->run(pict);

    return 0;
}
