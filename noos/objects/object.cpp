#include "object.hpp"
namespace noos {
namespace object {

object::object(const json::const_iterator & object_it)
{
    if (object_it->find("up_left_point") == object_it->end()){
        throw std::runtime_error("no up left point param in object");
    }
    else {
        // Look for params x and y in up_left_point method
        auto coord_it = object_it->find("up_left_point");
        up_left_point(coord_it); 
    }
    if (object_it->find("down_right_point") == object_it->end()){
        throw std::runtime_error("no down right point param in object");
    }
    else {
        // Look for params x and y in down_right_point method
        auto coord_it = object_it->find("down_right_point");
        down_right_point(coord_it); 
    }
    if (object_it->find("confidence") == object_it->end()){
        throw std::runtime_error("no confidence param in object");
    }
    else {
        confidence = object_it->find("confidence")->get<float>();
    }
    if (object_it->find("label") == object_it->end()){
        throw std::runtime_error("no label param in object");
    }
    else {
        label = object_it->find("label")->get<std::string>();
    }
}

bool object::operator==(const object & rhs) const
{
    return ( this->top_left_x == rhs.top_left_x &&
             this->top_left_y == rhs.top_left_y &&
             this->bottom_right_x == rhs.bottom_right_x &&
             this->bottom_right_y == rhs.bottom_right_y);
}

void object::up_left_point(const json::const_iterator & coord_it)
{
      if (coord_it->find("x") == coord_it->end()) {
          throw std::runtime_error("no x param in up left point");  
      }
      else {
          top_left_x = coord_it->find("x")->get<float>();
      }
      if (coord_it->find("y") == coord_it->end()) {
          throw std::runtime_error("no y param in up left point");
      }
      else {
          top_left_y = coord_it->find("y")->get<float>();
      }
}

void object::down_right_point(const json::const_iterator & coord_it)
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
