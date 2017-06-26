#ifndef NOOS_CLOUD_VISION_BASE
#define NOOS_CLOUD_VISION_BASE
namespace noos {
namespace cloud {
/**
 * @brief base class for vision cloud classes - used mostly for static assertions
 * @version 0.7.3
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 * @date 11 June 2017
 */
struct vision_base 
{ 
    std::string json;
};
}
}
#endif
