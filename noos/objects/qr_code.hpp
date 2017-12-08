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
 * @brief class which should encapsulate a QR code
 * @version 0.7.0
 * @date 25 August 2016
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
struct qr_code
{
    /// coordinate x of the center of the QR position
    float centre_x;
    /// coordinate y of the center of the QR position
    float centre_y;
    /// message of the QR found
    std::string message;

    /// @brief construct a qr object from a json iterator
    qr_code(const json::const_iterator & qr_it);

    /// @brief method to pass the information to json
    json::object_t to_json() const;

    /// @brief Equality operator
    bool operator==(const qr_code & rhs) const;

    ///@brief check if a component of json exist
    bool check_component(const json::const_iterator & it,
                         std::string);
};
}
}
#endif
