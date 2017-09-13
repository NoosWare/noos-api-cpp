#include "face_recognition_obj.hpp"
namespace noos {
namespace object {

face_recognition_obj::face_recognition_obj(const json::const_iterator & face_it)
: face_rect(face_it->find("rect"))
{
    if (face_it->find("confidence") == face_it->end()){
        throw std::runtime_error("no confidence param in face_recognition_obj");
    }
    else {
        confidence = face_it->find("confidence")->get<double>();
    }
    if (face_it->find("label") == face_it->end()){
        throw std::runtime_error("no label param in face");
    }
    else {
        label = face_it->find("label")->get<std::string>();
    }
}

json::object_t face_recognition_obj::to_json() const
{
    json::object_t rest = {{"rect", face_rect.to_json()},
                           {"confidence", confidence}, 
                           {"label", label}};
    return rest;
}

bool face_recognition_obj::operator==(const face_recognition_obj & rhs) const
{
    return ( this->face_rect == rhs.face_rect &&
             this->confidence == rhs.confidence &&
             this->label == rhs.label );
}

}
}
