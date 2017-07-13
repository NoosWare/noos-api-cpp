template <class value_type>
orientation<value_type>::orientation(value_type roll,
                                     value_type pitch,
                                     value_type yaw)
{
    this->roll = roll;
    this->pitch = pitch;
    this->yaw = yaw;
}

template <class value_type>
orientation<value_type>::orientation(const json::const_iterator & it)
{
    if (it->find("roll") == it->end()) {
        throw std::runtime_error("no param roll in pose");
    }
    else {
        roll = it->find("roll")->get<value_type>();
    }
    if (it->find("pitch") == it->end()) {
        throw std::runtime_error("no param pitch in pose");
    }
    else {
        pitch = it->find("pitch")->get<value_type>();
    }
    if (it->find("yaw") == it->end()) {
        throw std::runtime_error("no param yaw in pose");
    }
    else {
        yaw = it->find("yaw")->get<value_type>();
    }
}

template <class value_type>
json::object_t orientation<value_type>::to_json() const
{
    json::object_t values = {{"roll", roll}, {"pitch", pitch}, {"yaw", yaw}};
    return values;
}

template <class value_type>
bool orientation<value_type>::operator==(const noos::object::orientation<value_type> & rhs) const
{
    return (this->roll  == rhs.roll) &&
           (this->pitch == rhs.pitch) &&
           (this->yaw   == rhs.yaw);
}
