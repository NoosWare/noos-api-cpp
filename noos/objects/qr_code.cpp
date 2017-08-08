#include "qr_code.hpp"
namespace noos {
namespace object {

qr_code::qr_code(const json::const_iterator & qr_it)
{
    if (check_component(qr_it, "x")) {
      centre_x = qr_it->find("x")->get<float>();
    }
    if (check_component(qr_it, "y")) {
      centre_y = qr_it->find("y")->get<float>();
    }
    if (check_component(qr_it, "message")) {
      message = qr_it->find("message")->get<std::string>();
    }
}

json::object_t qr_code::to_json() const
{
    json::object_t qr {{"x", centre_x}, 
                       {"y", centre_y},
                       {"message", message}};
    return qr;
}

bool qr_code::operator==(const qr_code & rhs) const
{
    return boost::iequals(this->message, rhs.message);
}

bool qr_code::check_component(const json::const_iterator & it,
                              std::string component)
{
    if (it->find(component) == it->end()) {
        throw std::runtime_error("no " + component + "param in up left point");  
    }
    return true;
}

}
}
