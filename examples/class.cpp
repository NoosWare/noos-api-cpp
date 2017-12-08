#include <noos/noos>
#include <vector>
#include <iostream>

/*
 * Example to check the possibles ways to use callable in a class
 */
using namespace noos::cloud;

/*
 * Class where multiple inheritance is used to have
 * different callable objects
 */
class multiple_inheritance
: public callable<face_detection, false>,
  public callable<human_detection, false>
{
public:
    multiple_inheritance(noos::object::picture pic)
    : callable<face_detection, false>([this] (const auto faces) { this->callback_face(faces);}, default_node, pic),
      callable<human_detection, false>([this] (const auto humans) { this->callback_human(humans);}, default_node, pic)
    {}

    void callback_face(std::vector<noos::object::face> faces) {
        std::cout << "Number of faces found : " << faces.size() << std::endl;
    }

    void callback_human(std::vector<noos::object::human> humans) {
        std::cout << "Number of humans found : " << humans.size() << std::endl;
    }

    void send()
    {
        callable<face_detection, false>::send();
        callable<human_detection, false>::send();
    }

};

/*
 * Class where composition is used to have
 * different callable objects
 */
class composition
{
public:
    composition(noos::object::picture pic)
    : query__([this] (const auto faces) { this->callback(faces);}, default_node, pic),
      human_query__([this] (const auto humans) { std::cout << "Humans: " << humans.size() << std::endl;}, 
                    default_node, pic)
    {}

    void callback(std::vector<noos::object::face> faces) {
        std::cout << "Faces: " << faces.size() << std::endl;
    }

    void send()
    {
        query__.send();
        human_query__.send();
    }

private:
    callable<face_detection, false> query__;
    callable<human_detection, false> human_query__;

};

/*
 * Class where callable is created without its member
 * object in the first place. It is created before send
 * the information to the platform.
 */
class no_object_ctr
{
public:
    no_object_ctr()
    : query__(std::bind(&no_object_ctr::callback, this, std::placeholders::_1), 
              default_node)
    {}

    void callback(std::vector<noos::object::person> people) {
        std::cout << "Faces recognised: " << people.size() << std::endl;
    }

    void send(noos::object::picture pic)
    {
        query__.object = face_recognition(pic);
        query__.send();
    }

private:
    callable<face_recognition, true> query__;

};

/*
 * MAIN
 */
int main(int argc, char **argv)
{
    auto pic = noos::object::picture("data/object_classes_picture_1.png");

    multiple_inheritance test(pic);
    test.send();

    composition test1(pic);
    test1.send();

    no_object_ctr test2;
    test2.send(pic); 
    test2.send(pic); 

    return 0;
}
