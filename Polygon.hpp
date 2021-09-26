#ifndef _POLYGON_H
#define _POLYGON_H
#include <memory>
#include <vector>
#include "Point2d.hpp"
using namespace std;


class Polygon
{

public:
  Polygon();
  int sides;
  uint32_t incolour;
  uint32_t boundcolour;
  shared_ptr<vector<shared_ptr<Point2d> > >  vertices;
  
  void addPoint2d(int x, int y);
  void shift(int x, int y);
  shared_ptr<Point2d> getCenter();
  void setCenter(int x, int y);
  
  
private:
  shared_ptr<Point2d> center;
  void calculateCenter();
  
  
};
#endif

