#ifndef _THINGSTATE_HPP
#define _THINGSTATE_HPP
#include <memory>
#include "Engine.h"

class ThingState 
{
public:
  Thing();
  shared_ptr<DisplayObject> displayObject;

  void display(Engine *engine);
}


#endif
