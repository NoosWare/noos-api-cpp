#include "time.hpp"
namespace noos {
namespace object {

time::time(std::chrono::nanoseconds timepoint)
{
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(timepoint);
    auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint);
    seconds = sec.count();
    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(nsec - sec).count();
}

time::time(const json::const_iterator & stamp)
{
    if (stamp->find("secs") == stamp->end()) {
        throw std::runtime_error("no sec in stamp");
    }
    else {
        seconds = stamp->find("secs")->get<uint32_t>();
    }
    if (stamp->find("nsecs") == stamp->end()) {
        throw std::runtime_error("no nsec in stamp");
    }
    else {
        nanoseconds = stamp->find("nsecs")->get<uint32_t>();
    }
}

json::object_t time::to_json() const
{
    json::object_t values = {{"secs", seconds}, {"nsecs", nanoseconds}};
    return values;
}

bool time::operator==(const noos::object::time & rhs) const
{
    return (this->seconds == rhs.seconds) && 
           (this->nanoseconds == rhs.nanoseconds);
}

}
}
