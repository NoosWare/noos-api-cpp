#include "qr_code.hpp"
namespace noos {
namespace object {

qr_code::qr_code(const json::const_iterator & qr_it)
{
    // TODO: MARIA
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

}
}
