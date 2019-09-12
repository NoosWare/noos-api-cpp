template <class value_type>
point<value_type>::point( value_type x_data,
                          value_type y_data,
                          value_type z_data)
{
    x = x_data;
    y = y_data;
    z = z_data;
}

template <class value_type>
point<value_type>::point(const json::const_iterator & position)
{
    if (position->find("x") == position->end()) {
        throw std::runtime_error("no param x in position");
    }
    else {
        x = position->find("x")->get<value_type>();
    }
    if (position->find("y") == position->end()) {
        throw std::runtime_error("no param y in position");
    }
    else {
        y = position->find("y")->get<value_type>();
    }
    if (position->find("z") == position->end()) {
        throw std::runtime_error("no param z in position");
    }
    else {
        z = position->find("z")->get<value_type>();
    }
}

template <class value_type>
json::object_t point<value_type>::to_json() const
{
    json::object_t values = {{"x", x}, {"y", y}, {"z", z}};
    return values;
}

template <class value_type>
bool point<value_type>::operator==(const noos::object::point<value_type> & rhs) const
{
    return (this->x == rhs.x) &&
           (this->y == rhs.y) &&
           (this->z == rhs.z);
}

//Point 2d
template <class value_type>
point2d<value_type>::point2d(value_type x_data,
                           value_type y_data)
{
    x = x_data;
    y = y_data;
}

template <class value_type>
point2d<value_type>::point2d(const json::const_iterator & position)
{
    if (position->find("x") == position->end()) {
        throw std::runtime_error("no param x");
    }
    else {
        x = position->find("x")->get<value_type>();
    }
    if (position->find("y") == position->end()) {
        throw std::runtime_error("no param y");
    }
    else {
        y = position->find("y")->get<value_type>();
    }
}

template <class value_type>
json::object_t point2d<value_type>::to_json() const
{
    json::object_t values = {{"x", x}, {"y", y}};
    return values;
}

template <class value_type>
bool point2d<value_type>::operator==(const noos::object::point2d<value_type> & rhs) const
{
    return (this->x == rhs.x) &&
           (this->y == rhs.y);
}
