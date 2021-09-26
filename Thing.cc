#include "Thing.hpp"
#include <iostream>
using namespace std;


const std::string Thing::on = "on";
const std::string Thing::in = "in";
const std::string Thing::over = "over";
const std::string Thing::under = "under";
const std::string Thing::behind = "behind";

const std::string Thing::chair = "Chair";
const std::string Thing::bed = "Bed";
const std::string Thing::table = "Table";
const std::string Thing::tree = "Tree";
const std::string Thing::bush = "Bush";
const std::string Thing::door = "Door";
const std::string Thing::sofa = "Sofa";
const std::string Thing::wardrobe = "Wardrobe";
const std::string Thing::largebox = "Largebox";

Thing::RelationMap Thing::relMap = initMap();
Thing::RelationStringMap Thing::relStrMap = initRelStrMap();
Thing::ThingMap Thing::thingMap = initThingMap();
Thing::ThingTypeToNameMap Thing::thingTypeToNameMap = initThingTypeToNameMap();
Thing::ThingTable Thing::thingTable = initThingTable();


Thing::Thing()
{
  displayObject = make_shared<DisplayObject>();
}


shared_ptr<vector<RELATION> > Thing::getAllowedRelationsForCmdType(CommandType commandType)
{
  return allowedRelMap.find(commandType)->second;
}

void Thing::setName(std::string name)
{
  this->name = name;
}
std::string Thing::getName()
{
  return name;
}

void Thing::setFilename(std::string filename)
{
  displayObject->setFilename(filename);
}

std::string Thing::getFilename()
{
  return filename;
}

bool Thing::isEmpty()
{
  return isempty;
}

shared_ptr<Thing> Thing::makeThing(std::string type)
{
  
  shared_ptr<Thing> proto = thingTable.find(type)->second;
  if( proto == nullptr )
    return proto;
  return proto->clone();
}

shared_ptr<Thing> Thing::addThing(std::string type, shared_ptr<Thing> p)
{
  //std::cout<<"adding prototype  for thing type "<<type<<endl;
  
  thingTable[type] = p;
  //std::cout<<"done"<<endl;
  return p;
}

void Thing::display(Engine *engine)
{
  //std::cout<<"Thing::Display"<<endl;
  displayObject->display(engine);
  //std::cout<<"Thing::Display::end"<<endl;
}

shared_ptr<Point2d> Thing::getCenter()
{
  return displayObject->getCenter();
}

void Thing::setCenter(int x, int y)
{
  center->set(x, y);
  displayObject->setCenter(x, y);
}
