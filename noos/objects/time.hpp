#ifndef NOOS_OBJECT_TIME
#define NOOS_OBJECT_TIME
#include "includes.ihh"
/*
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @struct time
 * @brief Wraps around a time-stamp (UNIX Epoch)
 * @version 0.7.0
 * @date 19 August 2016
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
struct time
{
    uint32_t seconds;
    uint32_t nanoseconds;

    /**
     * @brief Construct using second and nanosecond
     * @param sec is system second
     * @param nsec is system nanosecond
     */
    time(std::chrono::nanoseconds timepoint);
    
    /// Construct using library "json for modern c++"
    time(const json::const_iterator & stamp);

    /// @brief Method to pass all the data into a json object
    json::object_t to_json() const;
    
    /// @brief Equality operator
    bool operator==(const noos::object::time & rhs) const;
};
}
}
#endif
