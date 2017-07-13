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
