#ifndef NOOS_OBJECT_QRCODE
#define NOOS_OBJECT_QRCODE
/*
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
namespace object {
/**
 * @class qr_code
 * @brief Class which encapsulate a QR code
 * @version 0.7.0
 * @date 25 August 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct qr_code
{
    /// Coordinate x of the center of the QR position
    float centre_x;
    /// Coordinate y of the center of the QR position
    float centre_y;
    /// Message of the QR found
    std::string message;

    /// @brief Construct a qr object from a json iterator
    qr_code(const json::const_iterator & qr_it);

    /// @brief Method to pass the information to json
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const qr_code & rhs) const;

    ///@brief Check if a component of json exist
    bool check_component(const json::const_iterator & it,
                         std::string);
};
}
}
#endif
