#include "Circle.hpp"

Circle::Circle()
{
  center = make_shared<Point2d>();
}

void Circle::addParameters(int x, int y, int radius, uint32_t colour)
{
  
  center->x = x;
  center->y = y;
  this->radius = radius;
  this->circumcolour = colour;
}

void Circle::shift(int x, int y)
{
  center->x += x;
  center->y += y;
}
