#ifndef NOOS_OBJECT_CONFIG_FILE
#define NOOS_OBJECT_CONFIG_FILE
#include "includes.ihh"
#include <noos/objects/globals.hpp>

namespace noos {
/// @brief Common object namespace
namespace object {
/**
 * @class config_file
 * @brief Class which convert a file into a std::string.
 *        Used for SLAM services.
 * @version 0.7.4
 * @date 1.09.2017
 */
class config_file
{
public:
    /// @brief Construct from a file 
    config_file(const std::string filepath);

    /// @brief Get data of the file
    std::string get_data();

private:
    std::string data__ = "";
};

}
}
#endif
