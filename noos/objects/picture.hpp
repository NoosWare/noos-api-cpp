#ifndef NOOS_OBJECT_PICTURE
#define NOOS_OBJECT_PICTURE
#include "includes.ihh"
#include <noos/objects/globals.hpp>
/**
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @class picture
 * @brief class which wraps around raw bytes of a picture
 * @version 0.7.0
 * @date August 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class picture
{
public:
    /// \brief Construct from a file-path
    picture(const std::string filepath);
        
    /// \brief Construct using an open file stream
    picture(std::ifstream & bytestream);

    /// \brief Constructor using the raw bytes of a file
    picture(const std::vector<noos::types::byte> data);

    /// \brief Copy constructor
    picture(const picture &) = default;
    
    /// \brief Assignment operator
    picture & operator=(const picture &) = default;

    /// \brief Picture equality
    bool operator==(const picture & rhs) const;

    /// \brief Not picture equality
    bool operator!=(const picture & rhs) const;

    /// \brief Get picture as array of bytes
    std::vector<noos::types::byte> bytearray() const;

    /// \brief Get image type (JPG/PNG supported)
    std::string type() const;

    /// \brief Save picture to filepath
    bool save(const std::string filepath);

private:
	typedef char byte;

    /// \brief Delete empty constructor    
    picture() = delete;

    /// \brief Parse the bytestream into the bytearray
    void opencb_(std::ifstream & bytestream);
        
    /// Members
    std::vector<noos::types::byte> bytearray_;
    std::string imgtype_;
};
}
}
#endif
