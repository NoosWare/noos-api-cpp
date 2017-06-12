#ifndef NOOS_OBJECT_QRCODE
#define NOOS_OBJECT_QRCODE
/**
 * LICENSE HERE
 */
#include "includes.ihh"
namespace noos {
namespace object {
/**
 * \class qrCode
 * \brief class which should encapsulate a QR code
 * \version 0.7.0
 * \date 25 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qr_code
{
public:
    /**
     * \brief Construct using code coordinates (a rectangle) and a label (URL, email, string, etc)
     * \param centre_x is coordinate
     * \param centre_y is coordinate
     * \param label is message embedded in QR
     */
    qr_code( 
              float centre_x,
              float centre_y,
              std::string label
           );
    
    /// \brief Allow Empty Constructor
    qr_code() = default;
    
    /// \brief Copy Constructor
    qr_code(const qr_code &) = default;
    
    /// \brief constructor using json - not used in 0.7.0
    //qr_code(const json::const_iterator & qr_it);

    /// \brief method to pass the information to json
    json::object_t to_json() const;

    /** 
     * \brief Equality operator
     * \note the message is case insensitvely compared
     */
    bool operator==(const qr_code & rhs) const;

    /// \brief Get the qr Label
    std::string label() const;
    
private:
      float centre_x__ = -1;
      float centre_y__ = -1;
      std::string message__ ;
};
}
}
#endif
