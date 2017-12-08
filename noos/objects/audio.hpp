#ifndef NOOS_OBJECT_AUDIO
#define NOOS_OBJECT_AUDIO
#include "includes.ihh"
#include <noos/objects/globals.hpp>
/*
 * LICENSE HERE
 */
namespace noos {
/// @brief common object namespace
namespace object {
/**
 * @class audio
 * @brief class which wraps around raw bytes of an audiofile
 * @version 0.7.3
 * @date 10 June 2017
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
  */
class audio
{
public:
    /// @brief Construct from a file on disk
    audio(const std::string filepath);

    /// @brief Construct using an open file stream
    /// @param bytestream will be **consumed** by the object
    audio(std::ifstream & bytestream);

    /// @brief Construct using an existing byte-array
    /// @param bytearray should contain the audio data
    audio(std::vector<noos::types::byte> bytearray);

    /// @brief Copy constructor
    audio(const audio &) = default;

    /// @brief Get audio as array of bytes
    std::vector<noos::types::byte> bytearray() const;

    /// @brief Equality operator
    bool operator==(const audio & rhs) const;

    /// @brief Inequality operator
    bool operator!=(const audio & rhs) const;

    /// @brief Assignment operator
    audio & operator=(const audio &) = default;

    /// @brief Save audio to filepath
    bool save(const std::string filepath);
    
private:
    // Delete empty constructor    
    audio() = delete;
    // Copy the bytestream into the bytearray
    void read_bytes(std::ifstream & bytestream);
    // Actual bytes of audio file
    std::vector<noos::types::byte> bytearray_;
};

}
}
#endif
