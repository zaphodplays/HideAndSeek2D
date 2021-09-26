#ifndef _LINE_HPP
#define _LINE_HPP
#include "Point2d.hpp"
#include <memory>

class Line
{
public:

  Line();

  shared_ptr<Point2d> point1;
  shared_ptr<Point2d> point2;
  uint32_t linecolour;

  void addPoints(int x1, int y1, int x2, int y2);
  void setColour(uint32_t colour);

  void shift(int x, int y);

};

#endif
