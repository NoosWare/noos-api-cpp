#ifndef NOOS_CLOUD_DESERIALIZE_HPP
#define NOOS_CLOUD_DESERIALIZE_HPP
/**
 * LICENSE HERE
 */
#include <noos/objects.hpp>
#include <noos/misc/misc.hpp>
namespace noos {
namespace cloud {
/// Generic template
template <class service_type, 
          class return_type>
struct deserialize
{
    return_type operator()(std::string json);
};

}
}
#endif
