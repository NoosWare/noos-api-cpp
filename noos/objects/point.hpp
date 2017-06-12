#ifndef NOOS_OBJECT_POINT
#define NOOS_OBJECT_POINT
#include "includes.ihh"
/**
 * LICENSE HERE
 */
namespace noos {
namespace object {
/**
 * @struct point
 * @brief encapsulate point position vector
 * @version 0.7.0
 * @date 19 August 2016
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class point
{
public:
    /**
     * @brief Construct using code coordinates (x,y,z)
     * @param x is x coordinate
     * @param y is y coordinate
     * @param z is z coordinate
     */
    point(double x, double y, double z);
    
    /// \brief Allow Empty Constructor
    point() = default;
    
    /// \brief Copy Constructor
    point(const noos::object::point &) = default;

    /// \brief Construct using library "json for modern c++"
    point(const json::const_iterator & position);
   
    /// \return a JSON object
    json::object_t to_json() const;
   
    /// \brief Equality operator
    bool operator==(const noos::object::point & rhs) const;

    /// \return parameter x
    double get_x() const;

    /// \return parameter y
    double get_y() const;

    /// \return parameter z
    double get_z() const;

private:
    /// members
	double x = 0;
    double y = 0;
    double z = 0;
};
}
}
#endif
