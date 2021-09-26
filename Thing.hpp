#ifndef _THING_H
#define _THING_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "DisplayObject.hpp"
#include "Engine.h"
#include "Enums.hpp"



using namespace std;

  

class Thing
{

private:
  std::string name;
  std::string filename;

  virtual shared_ptr<Thing> clone() = 0;
public:
  Thing();
  static shared_ptr<Thing> makeThing(std::string type);
  static shared_ptr<Thing>  addThing(std::string type, shared_ptr<Thing> thing);

  void setName(std::string name);
  std::string getName();

  void setFilename(std::string filename);
  std::string getFilename();

  virtual shared_ptr<vector<RELATION> > getAllowedRelationsForCmdType(CommandType commandType) ;
  bool isEmpty();
  typedef map<const std::string, RELATION> RelationMap;
  static RelationMap relMap;
  ThingType thingtype;
  
  typedef map<const std::string, ThingType> ThingMap;
  static ThingMap thingMap;
  
  typedef map<std::string, shared_ptr<Thing> > ThingTable;
  static ThingTable thingTable;
  
  typedef map<ThingType, std::string> ThingTypeToNameMap;
  static ThingTypeToNameMap thingTypeToNameMap;

  typedef map<CommandType, shared_ptr< vector<RELATION> >  > AllowedRelMap;
  
  typedef map<RELATION, std::string> RelationStringMap;
  static RelationStringMap relStrMap;

  shared_ptr<DisplayObject> displayObject;

  void display(Engine *engine);

  shared_ptr<Point2d> getCenter();

  void setCenter(int x, int y);

  protected:
  
  virtual void initAllowedRelations() = 0 ;
    
  bool isempty;
  shared_ptr<Point2d> center;
  AllowedRelMap allowedRelMap;

  
  public:
    static const std::string on;
    static const std::string in;
    static const std::string over;
    static const std::string under;
    static const std::string behind;

    static const std::string chair;
    static const std::string bed;
    static const std::string table;
    static const std::string tree;
    static const std::string bush;
    static const std::string door;
    static const std::string sofa;
    static const std::string wardrobe;
    static const std::string largebox;

  static ThingTypeToNameMap initThingTypeToNameMap()
  {
    ThingTypeToNameMap tMap;
    tMap[CHAIR] = chair;
    tMap[BED] = bed;
    tMap[TABLE] = table;
    tMap[TREE] = tree;
    tMap[BUSH] = bush;
    tMap[DOOR] = door;
    tMap[SOFA] = sofa;
    tMap[WARDROBE] = wardrobe;
    tMap[LARGEBOX] = largebox;
    return tMap;
  }
  private:
    static RelationMap initMap() {
      RelationMap someMap;
      someMap[on] = ON;
      someMap[in] = IN;
      someMap[over] = OVER;
      someMap[under] = UNDER;
      someMap[behind] = BEHIND;
      return someMap;

    }

  

    static ThingMap initThingMap() {
      ThingMap sMap;
      sMap[chair] = CHAIR;
      sMap[bed] = BED;
      sMap[table] = TABLE;
      sMap[tree] = TREE;
      sMap[bush] = BUSH;
      sMap[door] = DOOR;
      sMap[sofa] = SOFA;
      sMap[wardrobe] = WARDROBE;
      sMap[largebox] = LARGEBOX;
      return sMap;
    }

    static ThingTable initThingTable() {
      ThingTable sTable;
      return sTable;
    }

  static RelationStringMap initRelStrMap()
  {
    RelationStringMap rsMap;
    rsMap[ON] = on;
    rsMap[IN] = in;
    rsMap[OVER] = over;
    rsMap[UNDER] = under;
    rsMap[BEHIND] = behind;
    return rsMap;
  }

  

   


};

#define _CLONE(TYPE) \
  virtual shared_ptr<Thing> clone()  { return  make_shared<TYPE>(); }

#define MAKE_PROTOTYPE(TYPE) \
  shared_ptr<Thing> TYPE ## _p(new TYPE());	\
   shared_ptr<Thing> TYPE ## _myProtoype = \
     Thing::addThing(#TYPE, TYPE ## _p);


#endif
