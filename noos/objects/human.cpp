#include "human.hpp"
namespace noos {
namespace object {

human::human(const json::const_iterator & human_it)
{
    if (human_it->find("up_left_point") == human_it->end()){
        throw std::runtime_error("no up left point param in human");
    }
    else {
        auto coord_it = human_it->find("up_left_point");
        up_left_point(coord_it); 
    }
    if (human_it->find("down_right_point") == human_it->end()){
        throw std::runtime_error("no down right point param in human");
    }
    else {
        auto coord_it = human_it->find("down_right_point");
        down_right_point(coord_it); 
    }
}

json::object_t human::to_json() const
{
    json::object_t value_up = {{"x", top_left_x}, 
                               {"y", top_left_y}};
    json::object_t value_dowm = {{"x", bottom_right_x}, 
                                 {"y", bottom_right_y}};
    json::object_t both = {{"up_left_point", value_up}, 
                           {"down_right_point", value_dowm}};
    return both;
}

bool human::operator==(const human & rhs) const
{
    return (this->top_left_x     == rhs.top_left_x &&
            this->top_left_y     == rhs.top_left_y &&
            this->bottom_right_x == rhs.bottom_right_x &&
            this->bottom_right_y == rhs.bottom_right_y);
}

void human::up_left_point(const json::const_iterator & coord_it)
{
    if (coord_it->find("x") == coord_it->end()){
        throw std::runtime_error("no x param in up left point");  
    }
    else {
        top_left_x = coord_it->find("x")->get<float>();
    }
    if (coord_it->find("y") == coord_it->end()){
        throw std::runtime_error("no y param in up left point");
    }
    else {
        top_left_y = coord_it->find("y")->get<float>();
    }
}

void human::down_right_point(const json::const_iterator & coord_it)
{
    if (coord_it->find("x") == coord_it->end()){
        throw std::runtime_error("no x param in down right point");  
    }
    else {
        bottom_right_x = coord_it->find("x")->get<float>();
    }
    if (coord_it->find("y") == coord_it->end()){
        throw std::runtime_error("no y param in down right point");  
    }
    else {
        bottom_right_y = coord_it->find("y")->get<float>();
    }
}

}
}
