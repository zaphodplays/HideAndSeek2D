#ifndef _ANIMATIONSEQUENCE_HPP
#define _ANIMATIONSEQUENCE_HPP
#include "DisplayObject.hpp"
#include <vector>
#include <iostream>
#include "Point2d.hpp"

class AnimationSequence 
{
  shared_ptr<vector<shared_ptr<DisplayObject> > > animation;
  std::string name;
  uint32_t colour;
  int index;

public:

  AnimationSequence();

  void setName(const std::string &name);

  void setColour(uint32_t dresscolour);
  
  void addImage(shared_ptr<DisplayObject> dimage);

  shared_ptr<DisplayObject> getDisplayObject(int pos);

  void shiftDisplays(int x, int y);

  int getSize();

  void display(Engine* engine);

  shared_ptr<Point2d>  getCenter();

    
};
#endif
