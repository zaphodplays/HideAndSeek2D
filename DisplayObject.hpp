#ifndef _DISPLAYOBJECT_H
#define _DISPLAYOBJECT_H
#include <string>
#include "Engine.h"
#include "TextObject.hpp"
using namespace std;


class DisplayObject
{
  
  public:
  shared_ptr<TextObject> textObject;
  shared_ptr<Point2d> center;
  std::string filename;

  
    
    typedef shared_ptr<DisplayObject> DO_PTR;
    static DO_PTR  DO_NOT_FOUND;

  


public:
  DisplayObject();
  DisplayObject(std::string filename, int x, int y);
  
  shared_ptr<TextObject> getTextObject();
  shared_ptr<Point2d> getCenter();
  
  
  void setFilename(std::string filename);
  
  void setText(std::string text, int x, int y);
  void setCenter(int x, int y);

public:
  void display(Engine *engine);
  void shift(int x, int y);
  //shared_ptr<DisplayObject> clone();

private:
  
  void drawText(Engine *engine);
  void drawImage(Engine *engine );

};
#endif
