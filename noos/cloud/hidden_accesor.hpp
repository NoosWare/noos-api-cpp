#ifndef NOOS_HIDDEN_ACCESOR_HPP
#define NOOS_HIDDEN_ACCESOR_HPP
#include <noos/cloud/includes.ihh>
namespace noos {
namespace cloud {

/*
 * @brief template class to access to
 *        empty constructors
 * @struct hidden_accesor
 * @date 13.09.2017
 * @version 0.8.0
 */
template <class cloud_class>
struct hidden_accesor 
: protected cloud_class
{
    // @brief empty constructor
    hidden_accesor() = default;
};

}
}
#endif 
