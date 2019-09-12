template <class value_type>
pose<value_type>::pose(  point<value_type> coordinates,
                         orientation<value_type> angles)
{
    this->coordinates = coordinates;
    this->angles = angles;
}

template <class value_type>
pose<value_type>::pose(const json::const_iterator & it)
{
    if (it->find("position") == it->end()) {
        throw std::runtime_error("no param position in pose");
    }
    else {
        coordinates = point<value_type>(it->find("position"));
    }
    if (it->find("orientation") == it->end()) {
        throw std::runtime_error("no param orientation pose");
    }
    else {
        angles = orientation<value_type>(it->find("orientation"));
    }
}

template <class value_type>
json::object_t pose<value_type>::to_json() const
{
    json::object_t values = {{"position", coordinates.to_json()},
                             {"orientation", angles.to_json()}};
    return values;
}

template <class value_type>
bool pose<value_type>::operator==(const noos::object::pose<value_type> & rhs) const
{
    return (this->coordinates == rhs.coordinates) &&
           (this->angles  == rhs.angles);
} 

//Pose 2d
template <class value_type>
pose2d<value_type>::pose2d(value_type x_data,
                           value_type y_data,
                           value_type theta_data)
: x(x_data),
  y(y_data),
  theta(theta_data)
{}

template <class value_type>
pose2d<value_type>::pose2d(const json::const_iterator & position)
{
    if (position->find("x") == position->end()) {
        throw std::runtime_error("no param x in points");
    }
    else {
        x = position->find("x")->get<value_type>();
    }
    if (position->find("y") == position->end()) {
        throw std::runtime_error("no param y in points");
    }
    else {
        y = position->find("y")->get<value_type>();
    }
    if (position->find("theta") == position->end()) {
        throw std::runtime_error("no param theta in points");
    }
    else {
        theta = position->find("theta")->get<value_type>();
    }
}

template <class value_type>
json::object_t pose2d<value_type>::to_json() const
{
    json::object_t values = {{"x", x}, 
                             {"y", y}, 
                             {"theta", theta}};
    return values;
}

template <class value_type>
bool pose2d<value_type>::operator==(const noos::object::pose2d<value_type> & rhs) const
{
    return (this->x == rhs.x) &&
           (this->y == rhs.y) &&
           (this->theta == rhs.theta);
}
