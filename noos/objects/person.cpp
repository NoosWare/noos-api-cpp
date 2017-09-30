#include "person.hpp"
namespace noos {
namespace object {

person::person(const json::const_iterator & face_it)
: face_rect(face_it->find("rect"))
{
    if (face_it->find("confidence") == face_it->end()){
        throw std::runtime_error("no confidence param in person");
    }
    else {
        confidence = face_it->find("confidence")->get<float>();
    }
    if (face_it->find("label") == face_it->end()){
        throw std::runtime_error("no label param in face");
    }
    else {
        label = face_it->find("label")->get<int>();
    }
    if (face_it->find("name") == face_it->end()){
        throw std::runtime_error("no name param in face");
    }
    else {
        name = face_it->find("name")->get<std::string>();
    }
}

json::object_t person::to_json() const
{
    json::object_t rest = {{"rect", face_rect.to_json()},
                           {"confidence", confidence}, 
                           {"label", label},
                           {"name", name}};
    return rest;
}

bool person::operator==(const person & rhs) const
{
    return ( this->face_rect == rhs.face_rect &&
             this->confidence == rhs.confidence &&
             this->name == rhs.name &&
             this->label == rhs.label );
}

}
}
