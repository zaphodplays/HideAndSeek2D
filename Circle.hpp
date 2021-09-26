#ifndef _CIRCLE_HPP
#define _CIRCLE_HPP
#include <memory>
#include "Point2d.hpp"

class Circle
{
public:

  Circle();
  uint32_t circumcolour;
  shared_ptr<Point2d> center;
  int radius;

  void addParameters(int x, int y, int radius, uint32_t colour);

  void shift(int x, int y);
};
#endif
