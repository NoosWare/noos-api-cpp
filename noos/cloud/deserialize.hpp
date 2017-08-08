#ifndef NOOS_CLOUD_DESERIALIZE_HPP
#define NOOS_CLOUD_DESERIALIZE_HPP
/*
 * LICENSE HERE
 */
#include <noos/objects.hpp>
#include <noos/misc/misc.hpp>
namespace noos {
namespace cloud {
/**
 * @brief deserialize a json string to noos::object::*
 * this struct uses template specialisation for each service_type and return_type pair
 * the template parameter `service_type` is a cloud class
 * the template parameter `return_type` is the data (object) returned
 */
template <class service_type, 
          class return_type>
struct deserialize
{
    return_type operator()(std::string json);
};

}
}
#endif
