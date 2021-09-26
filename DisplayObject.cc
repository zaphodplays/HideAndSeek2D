#include "DisplayObject.hpp"
#include <iostream>


//DisplayObject::DO_PTR DisplayObject::DO_NOT_FOUND = DisplayObject::initializeDO();

DisplayObject::DisplayObject()
{
  
  
  textObject = make_shared<TextObject>();
  center = make_shared<Point2d>();
}

DisplayObject::DisplayObject(std::string filename, int x, int y) {
  this->filename = filename;
  
  textObject = make_shared<TextObject>();
  center = make_shared<Point2d>();
  center->set(x,y);
  
}



void DisplayObject::setFilename(std::string filename)
{
  this->filename = filename;
}



void DisplayObject::setText(std::string text, int x, int y)
{
  textObject->setText(text);
  textObject->setLocation(x, y);
}







shared_ptr<TextObject> DisplayObject::getTextObject()
{
  return textObject;
}

shared_ptr<Point2d> DisplayObject::getCenter()
{
  return center;
}

void DisplayObject::setCenter(int x, int y)
{
  center->x = x;
  center->y = y;
}

void DisplayObject::display(Engine *engine)
{
  //drawCircles(engine);
  //drawPolygons(engine);
  //drawCircles(engine);
  //drawLines(engine);
  //drawText(engine);
  drawImage(engine);
  
}



void DisplayObject::drawText(Engine *engine)
{
  engine->drawText(textObject->getText().c_str(), textObject->getLocation()->x, textObject->getLocation()->y);
}

void DisplayObject::drawImage(Engine *engine)
{
  engine->drawImage(filename, center->x, center->y);
}


void DisplayObject::shift(int x, int y)
{
  center->x += x;
  center->y += y;
  
  
  textObject->shift(x, y);
}

