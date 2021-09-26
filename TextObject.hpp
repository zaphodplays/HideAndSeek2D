#ifndef _TEXTOBJECT_HPP
#define _TEXTOBJECT_HPP
#include <memory>
#include <string>
#include "Point2d.hpp"
using namespace std;

class TextObject
{
private:
  
  
  std::string text;
  shared_ptr<Point2d> location;

public:

  TextObject();
  std::string& getText();
  void setText(std::string &text);
  
  shared_ptr<Point2d> getLocation();
  void setLocation(int x, int y);

  void shift(int x, int y);
  
};
#endif
