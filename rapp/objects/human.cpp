#include "human.hpp"
namespace rapp {
namespace object {

human::human( 
      float top_left_x,
      float top_left_y,
      float bottom_right_x,
      float bottom_right_y
    )
: top_left_x__(top_left_x),
  top_left_y__(top_left_y),
  bottom_right_x__(bottom_right_x),
  bottom_right_y__(bottom_right_y)
{}

human::human(const json::const_iterator & human_it)
{
   if (human_it->find("up_left_point") == human_it->end()){
      throw std::runtime_error("no up left point param in human");
   }
   else {
      // Look for params x and y in up_left_point method
      auto coord_it = human_it->find("up_left_point");
      up_left_point(coord_it); 
   }

  if (human_it->find("down_right_point") == human_it->end()){
     throw std::runtime_error("no down right point param in human");
  }
  else {
      // Look for params x and y in down_right_point method
      auto coord_it = human_it->find("down_right_point");
      down_right_point(coord_it); 
  }

}

json::object_t human::to_json() const
{
    json::object_t value_up = {{"x", top_left_x__}, 
                               {"y", top_left_y__}};

    json::object_t value_dowm = {{"x", bottom_right_x__}, 
                                 {"y", bottom_right_y__}};

    json::object_t both = {{"up_left_point", value_up}, 
                           {"down_right_point", value_dowm}};
    
    return both;
}

bool human::operator==(const human & rhs) const
{
    return ( this->top_left_x__ == rhs.top_left_x__ &&
             this->top_left_y__ == rhs.top_left_y__ &&
             this->bottom_right_x__ == rhs.bottom_right_x__ &&
             this->bottom_right_y__ == rhs.bottom_right_y__);
}

float human::get_left_x() const
{
   return top_left_x__;
} 

float human::get_left_y() const
{
   return top_left_y__;
}

float human::get_right_x() const 
{
    return bottom_right_x__;
}

float human::get_right_y() const
{
    return bottom_right_y__;
}

void human::up_left_point(const json::const_iterator & coord_it)
{
      if (coord_it->find("x") == coord_it->end()){
          throw std::runtime_error("no x param in up left point");  
      }
      else {
          top_left_x__ = coord_it->find("x")->get<float>();
      }
      
      if (coord_it->find("y") == coord_it->end()){
          throw std::runtime_error("no y param in up left point");
      }
      else {
          top_left_y__ = coord_it->find("y")->get<float>();
      }
}

void human::down_right_point(const json::const_iterator & coord_it)
{
      if (coord_it->find("x") == coord_it->end()){
          throw std::runtime_error("no x param in down right point");  
      }
      else {
          bottom_right_x__ = coord_it->find("x")->get<float>();
      }

      if (coord_it->find("y") == coord_it->end()){
          throw std::runtime_error("no y param in down right point");  
      }
      else {
          bottom_right_y__ = coord_it->find("y")->get<float>();
      }
}

}
}