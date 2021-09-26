#ifndef _POINT2D_H
#define _POINT2D_H
#include <memory>
using namespace std;

class Point2d
{

public:
  int x;
  int y;

public:
  Point2d();
  void set(int x, int y);
  inline friend bool operator==(const Point2d& lhs, const Point2d& rhs){ return (lhs.x == rhs.x) && (lhs.y == rhs.y); }
  //shared_ptr<Point2d> 
  
};
#endif
