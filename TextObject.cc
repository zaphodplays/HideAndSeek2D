#include "TextObject.hpp"

TextObject::TextObject()
{
  location = make_shared<Point2d>();
  text = "";
}

void TextObject::setText(std::string &text)
{
  this->text = text;
}

std::string& TextObject::getText()
{
  return text;
}

void TextObject::setLocation(int x, int y)
{
  location->x = x;
  location->y = y;
}

shared_ptr<Point2d> TextObject::getLocation()
{
  return location;
}

void TextObject::shift(int x, int y)
{
  location->x += x;
  location->y += y;
}


