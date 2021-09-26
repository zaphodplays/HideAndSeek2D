#ifndef _DOOR_HPP
#define _DOOR_HPP
#include <map>
#include "Enums.hpp"
#include "Engine.h"
#include "Point2d.hpp"
#include "Polygon.hpp"
#include "DisplayObject.hpp"

using namespace std;

class Door
{
  
public:
  Door();
 
  
public:
  //Direction getDirection();
  //void setDirection(Direction direction);
  
  typedef int RoomID;
  void addDisplay(RoomID id, DoorType type);
  void display(Engine *engine, RoomID id);
  shared_ptr<Point2d> getCenter(RoomID id);
  typedef shared_ptr<DisplayObject> Doorgon;
  static Doorgon leftdoor;
  static Doorgon  rightdoor;
  static Doorgon  frontdoor;
  static Doorgon backdoor;
  static Doorgon topdoor;
  static Doorgon bottomdoor;
  //static shared_ptr<Polygon> southdoor;
private:
  
  
  
  shared_ptr<map<RoomID, shared_ptr<DisplayObject> > > doorDisplayMap;
  
  static Doorgon initLeftDoor()
  {
    Doorgon doorgon = make_shared<DisplayObject>("leftdoor.png", 128, 291);
    //{ (128, 291), (176, 285), (176, 283), (128, 411) }                                                                                                                                                                                     
   
    
    
    return doorgon;
  } 

  static Doorgon initRightDoor()
  {
    Doorgon doorgon = make_shared<DisplayObject>("rightdoor.png", 572, 301);
    //    { (572, 301), (618, 328), (618, 457), (572, 409) }                                                                                                                                                                                     
   
    
    return doorgon;
  }

  static Doorgon initFrontDoor()
  {
    Doorgon doorgon = make_shared<DisplayObject>("frontdoor.png", 416, 260);
    //{(416, 260), (482, 260}, (482, 360), (416, 360)  }
    
    
    return doorgon;
  }

  static Doorgon initBackDoor()
  {
    Doorgon doorgon = make_shared<DisplayObject>("backdoor.png", 620, 370);
    //{(620, 370), (639, 370}, (639, 479), (620, 479)  }
   
   
    return doorgon;
  }

  static Doorgon initTopDoor()
  {
    Doorgon doorgon = make_shared<DisplayObject>("frontdoor.png", 200, 75);
    //{(156, 56), (236, 56}, (248, 100), (168, 100)  }
  
   
    return doorgon;
  }

  static Doorgon initBottomDoor()
  {
    Doorgon doorgon = make_shared<DisplayObject>("frontdoor.png", 150, 435);
    //{(150, 435), (235, 435}, (205, 465), (105, 465)  }
   
    
    return doorgon;
  }

  typedef shared_ptr<map<DoorType, shared_ptr<DisplayObject> > > DoorTypeMap;
  static DoorTypeMap doorTypeMap;

  static DoorTypeMap initDoorTypeMap()
  {
    shared_ptr<map<DoorType, shared_ptr<DisplayObject> > > dmap = make_shared<map<DoorType, shared_ptr<DisplayObject> > >();
    (*dmap)[LEFT] = leftdoor;
    (*dmap)[RIGHT] = rightdoor;
    (*dmap)[FRONT] = frontdoor;
    (*dmap)[BACK] = backdoor;
    (*dmap)[TOP] = topdoor;
    (*dmap)[BOTTOM] = bottomdoor;
    return dmap;
  }

public:
  typedef shared_ptr<map<Direction, std::string> > DirShortNameMap;
  static DirShortNameMap dirShortNameMap;

  static DirShortNameMap initDirShortNameMap()
  {
    shared_ptr<map<Direction, std::string> > dsmap = make_shared<map<Direction, std::string > >();
    (*dsmap)[WEST] = "W";
    (*dsmap)[NORTH] = "N";
    (*dsmap)[EAST] = "E";
    (*dsmap)[SOUTH] = "S";
    (*dsmap)[UP] = "U";
    (*dsmap)[DOWN] = "D";
    return dsmap;
  }



};
#endif
