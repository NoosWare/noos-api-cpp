#ifndef DESERIALIZE_HPP
#define DESERIALIZE_HPP
/**
 *
 * LICENSE HERE
 *
 */
#include <rapp/objects.hpp>
namespace rapp {
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
