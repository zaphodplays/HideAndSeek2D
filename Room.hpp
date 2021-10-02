#ifndef _ROOM_H
#define _ROOM_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Enums.hpp"
#include "Thing.hpp"
#include "DisplayObject.hpp"
#include "Engine.h"
#include "Player.hpp"
#include "Door.hpp"

using namespace std;


class Player;
class Thing;

class Room :public enable_shared_from_this<Room> {


public:
  Room(std::string name, std::string filename, int x, int y);
  ~Room();


  shared_ptr< vector< shared_ptr<Thing> > >  things;
  shared_ptr<set<string> > inhabitants;
  shared_ptr< vector< Direction> > allowedDirections;

  shared_ptr<Thing> getThingOfType(ThingType type);
  
  int getID();
  void setID(int id);

  void setName(std::string name);
  std::string getName();

  void setFilename(std::string filename);
  std::string getFilename();
  
  shared_ptr<Room> move(Direction direction);
   
  shared_ptr<DisplayObject> displayObject;

  void display(Engine *engine);
  
  
  void listThings();
  shared_ptr<vector<shared_ptr<Thing> > >  getThings();

  bool hasLight();
  void toggleLight();

  bool userPlayerPresent();
  void toggleUserPlayerPresent();
  void setUserPlayerPresent();

  void addPlayer(std::string playername);
  void removePlayer(std::string playername);

  void addWall(DoorType doorType, shared_ptr<Door>);

  shared_ptr<Door> getDoorInDirection(Direction direction);
  
  //Room(int id, ROOMTYPE type);
  /**
   * A Room will have 5 displayable walls 
   **/
  shared_ptr<map<DoorType, shared_ptr<Door> > > wallDoorMap;
  shared_ptr<Room> getRoomInDirection(Direction direction);
  shared_ptr<map<Direction, DoorType> > wallTypeDirMap;
  shared_ptr<map<DoorType, Direction> > dirWallTypeMap;

  friend void connect(Direction direction, shared_ptr<Room> room1, shared_ptr<Room> room2);
  friend void setRoomInDirection(Direction direction, shared_ptr<Room> room1, shared_ptr<Room> room2);

  void setDirectionsToWalls(int wallNum);
  static const std::string north;
  static const std::string south;
  static const std::string west;
  static const std::string east;
  static const std::string up;
  static const std::string down;
  
  
  typedef map<const std::string, Direction> DirMap;
  typedef map<Direction, std::string> DirNameMap;
  static DirMap dirMap;
  static DirNameMap dirNameMap;

  static DirMap initDirMap() {
    DirMap someDirMap;
    someDirMap[north] = NORTH;
    someDirMap[south] = SOUTH;
    someDirMap[west] = WEST;
    someDirMap[east] = EAST;
    someDirMap[up] = UP;
    someDirMap[down] = DOWN;
    return someDirMap;
  }

  static DirNameMap initDirNameMap() {
    DirNameMap nameDirMap;
    nameDirMap[NORTH] = north;
    nameDirMap[SOUTH] = south;
    nameDirMap[WEST] = west;
    nameDirMap[EAST] = east;
    nameDirMap[UP] = up;
    nameDirMap[DOWN] = down;
    return nameDirMap;
  }

  typedef map<Direction, Direction> DirPairs;
  static DirPairs dirPairsMap;

  static DirPairs initDirPairsMap() {
    DirPairs someDirPairsMap;
    someDirPairsMap[NORTH] = SOUTH;
    someDirPairsMap[SOUTH] = NORTH;
    someDirPairsMap[WEST] = EAST;
    someDirPairsMap[EAST] = WEST;
    someDirPairsMap[UP] = DOWN;
    someDirPairsMap[DOWN] = UP;
    return someDirPairsMap;
  }
  
  typedef shared_ptr<map<int, shared_ptr<Room> > > RoomIDMap;
  static RoomIDMap roomIDMap;

  static RoomIDMap initRoomIDMap()
  {
    RoomIDMap ridMap = make_shared<map<int, shared_ptr<Room> > >();
    return ridMap;
  }

  
  static  Direction wnesud[DIRECTIONCount]; //west,north,east,south,up,down
  static  DoorType lfrbud[DoorCount]; //left,front,right,back,up,down
  





  

  

  
  static void setRoomInDirection(Direction direction, shared_ptr<Room> room1, shared_ptr<Room> room2)
  {
    (*(room1->directionMap))[direction] = room2;
    (*(room2->directionMap))[(Room::dirPairsMap.find(direction))->second] = room1;
    
    room1->allowedDirections->push_back(direction);
    room2->allowedDirections->push_back((Room::dirPairsMap.find(direction))->second);

  }

  static void connect(Direction direction, shared_ptr<Room> room1, shared_ptr<Room> room2)
  {
    std::cout<<"connect::begin"<<endl;
    Direction room2Direction = Room::dirPairsMap.find(direction)->second;
    if(room1->wallTypeDirMap->empty())
      {
        DoorType dType = lfrbud[wnesud[direction]];
        room1->setDirectionsToWalls(dType);
      }
    if(room2->wallTypeDirMap->empty())
      {
        DoorType dType = lfrbud[wnesud[room2Direction]];
        room2->setDirectionsToWalls(dType);
      }
    DoorType doorTypeRoom1 = room1->wallTypeDirMap->find(direction)->second;
    DoorType doorTypeRoom2 = room2->wallTypeDirMap->find(room2Direction)->second;
    shared_ptr<Door> door = make_shared<Door>();
    room1->addWall(doorTypeRoom1, door);
    room2->addWall(doorTypeRoom2, door);
    setRoomInDirection(direction, room1, room2);
    std::cout<<"connect::end"<<endl;
  }

  

private:
  //shared_ptr<map<Direction, shared_ptr<Door> > > roomDoorMap;
  shared_ptr<map<Direction, shared_ptr<Room> > > directionMap;
  int id;
  bool light;
  bool userPresent;
  std::string name;
  std::string filename;

};
#endif
