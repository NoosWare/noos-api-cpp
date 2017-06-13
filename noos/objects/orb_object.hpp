#ifndef NOOS_OBJECT_ORB_OBJECT
#define NOOS_OBJECT_ORB_OBJECT
/**
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
namespace object {
/**
 * @struct orb_object
 * @brief 
 * @version 0.7.2
 * @date 
 * @author 
 *
 * TODO: turn into a class, use descriptive names, load to/from json
 */
struct orb_object
{
    std::vector<std::string> names;
    std::vector<noos::object::point<double>> points; 
    std::vector<double> scores;
    int result;
};
}
}
#endif
