#include "Line.hpp"


Line::Line()
{
  point1 = make_shared<Point2d>();
  point2 = make_shared<Point2d>();
}

void Line::addPoints(int x1, int y1, int x2, int y2)
{
  point1->x = x1;
  point1->y = y1;
  point2->x = x2;
  point2->y = y2;
}

void Line::setColour(uint32_t colour)
{
  linecolour = colour;
}

void Line::shift(int x, int y)
{
  point1->x += x;
  point1->y += y;
  point2->x += x;
  point2->y += y;
}
