#include "Polygon.hpp"

Polygon::Polygon()
{
  vertices = make_shared<vector<shared_ptr<Point2d> > >();
  center = make_shared<Point2d>();
}

void Polygon::addPoint2d(int x, int y)
{
  shared_ptr<Point2d> p1 = make_shared<Point2d>();
  p1->x = x;
  p1->y = y;
  vertices->push_back(p1);
  //recalculate center everytime we add a new point
  calculateCenter();
}

void Polygon::calculateCenter()
{
  int num = vertices->size() - 1;
  if(num > 0)
    {
      center->x = 0;
      center->y = 0;
      for(int i = 0; i < num; i++)
	{
	  shared_ptr<Point2d> point = (*vertices)[i];
	  center->x += point->x;
	  center->y += point->y;
	}
      
      center->x = center->x/num;
      center->y = center->y/num;
    }
}

void Polygon::shift(int x, int y)
{
  for(shared_ptr<Point2d> point : *vertices)
    {
      point->x += x;
      point->y += y;
      center->x += x;
      center->y += y;
    }
}

shared_ptr<Point2d> Polygon::getCenter()
{
  return center;
}

void Polygon::setCenter(int x, int y)
{
  center->x = x;
  center->y = y;
}
