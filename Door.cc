#include "Door.hpp"
#include <iostream>
using namespace std;


Door::Doorgon Door::leftdoor = Door::initLeftDoor();
Door::Doorgon Door::rightdoor = Door::initRightDoor();
Door::Doorgon Door::frontdoor = Door::initFrontDoor();
Door::Doorgon Door::backdoor = Door::initBackDoor();
Door::Doorgon Door::topdoor = Door::initTopDoor();
Door::Doorgon Door::bottomdoor = Door::initBottomDoor();
Door::DoorTypeMap Door::doorTypeMap = Door::initDoorTypeMap();
Door::DirShortNameMap Door::dirShortNameMap = Door::initDirShortNameMap();

Door::Door()
{
  doorDisplayMap = make_shared<map<int, shared_ptr<DisplayObject> > >();
}

void Door::addDisplay(RoomID roomID, DoorType dType)
{
  std::cout<<"door::addDisplay:: for room "<<roomID<<" and doortype is "<<dType<<endl;
  shared_ptr<DisplayObject> dp = make_shared<DisplayObject>();
  
  std::cout<<"door::add polygon"<<endl;
  shared_ptr<Point2d> polycenter = doorTypeMap->find(dType)->second->getCenter();
  std::cout<<"door:: polycenter is x: "<<polycenter->x<<" y: "<<polycenter->y<<endl; 
  dp->setCenter(polycenter->x, polycenter->y);
  (*doorDisplayMap)[roomID] = dp;
  std::cout<<"door::addDisplay::end"<<endl;
}

void Door::display(Engine *engine, RoomID roomID)
{
  doorDisplayMap->find(roomID)->second->display(engine);
}

shared_ptr<Point2d> Door::getCenter(RoomID id)
{
  return doorDisplayMap->find(id)->second->getCenter();
  
}
