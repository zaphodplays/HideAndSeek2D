#include <iostream>
#include "Room.hpp"



/**Room::Room(int id, ROOMTYPE roomtype)
{
  this->id = id;
  this->roomtype = roomtype;
  }**/

const std::string Room::north = "north";
const std::string Room::south = "south";
const std::string Room::west = "west";
const std::string Room::east = "east";
const std::string Room::up = "up";
const std::string Room::down = "down";



Room::DirMap Room::dirMap = initDirMap();
Room::DirNameMap Room::dirNameMap = initDirNameMap();
Room::DirPairs Room::dirPairsMap = initDirPairsMap();

Room::RoomIDMap Room::roomIDMap = initRoomIDMap();
Direction Room::wnesud[DIRECTIONCount] = {WEST, NORTH, EAST, SOUTH, UP, DOWN};
DoorType Room::lfrbud[DoorCount] = {LEFT, FRONT, RIGHT, BACK, TOP, BOTTOM};
//shared_ptr<DisplayObject> Room::closedroom = Room::initClosedRoom();
//shared_ptr<DisplayObject> Room::openroom = Room::initOpenRoom();


Room::Room(int id, std::string name, std::string filename, int x, int y)
{
  assert(roomIDMap->find(id) == roomIDMap->end());
  setID(id);
  userPresent = false;
  this->name = name;
  displayObject = make_shared<DisplayObject>(filename, x, y);
  displayObject->setText(name, 300, 50);
  things = make_shared< vector < shared_ptr<Thing> > >();
  directionMap = make_shared< map< Direction , shared_ptr<Room> > >();
  inhabitants = make_shared< set< std::string > >();
  allowedDirections = make_shared< vector < Direction > >();
  wallTypeDirMap = make_shared<map<Direction, DoorType> >();
  dirWallTypeMap = make_shared<map<DoorType, Direction> >();
  wallDoorMap = make_shared<map<DoorType, shared_ptr<Door> > >();
  
  //(*roomIDMap)[id] = shared_from_this(); 
}

Room::~Room()
{
  std::cout<<"destructor called!"<<endl;
}

int Room::getID()
{
  return id;
}

void Room::setName(std::string name)
{
  this->name = name;
  displayObject->setText(name, 300, 50);
}
std::string Room::getName()
{
  return name;
}

void Room::setFilename(std::string filename)
{
  this->filename = filename;
  displayObject->setFilename(filename);
}

std::string Room::getFilename()
{
  return filename;
}

void Room::setID(int id)
{
  this->id = id;
  //(*roomIDMap)[id] = shared_from_this();
}







void Room::display(Engine *engine)
{
    displayObject->display(engine);
    std::cout<<"displayed room object"<<endl;
    map<DoorType, shared_ptr<Door> >::iterator it;

    for ( it = wallDoorMap->begin(); it != wallDoorMap->end(); it++ )
      {
        //std::cout << it->first  // std::string (key)
        //	  << ':'
        //	  << it->second   // std::string's value 
        //	  << std::endl ;
        if(it->first == BACK)
          continue;
        it->second->display(engine, id);
        DoorType dType = it->first;
        Direction dir = dirWallTypeMap->find(dType)->second;
        std::string dirName = Door::dirShortNameMap->find(dir)->second;
        shared_ptr<Point2d> doorcenter = it->second->getCenter(id);
        engine->drawText(dirName.c_str(), doorcenter->x, doorcenter->y);
      }
      
      for(shared_ptr<Thing> thing : *things)
      {
        thing->display(engine);
      }
      std::cout<<"displayed things "<<endl;
    for(std::string playername : *inhabitants )
    {
      shared_ptr<Player> inhabitant = Player::playerNameMap->find(playername)->second;
      std::cout<<"player name = "<<inhabitant->getName()<<endl;
      inhabitant->role->stateStack->top()->displayState(engine, inhabitant);
      std::cout<<"displayed state "<<endl;
    }

    
}

shared_ptr<Room> Room::move(Direction direction)
{
  //std::cout<<"move:: direction"<<direction<<endl;
  switch(direction)
    {
    case NORTH:
      {
	//std::cout<<"new room is "<<(directionMap->find(NORTH)->second)->getRoomType()<<endl;
	return directionMap->find(NORTH)->second;
	break;
      }

    case SOUTH:
      {
	return directionMap->find(SOUTH)->second;
	break;
      }

    case WEST:
      {
	return directionMap->find(WEST)->second;
	break;
      }

    case EAST:
      {
	return directionMap->find(EAST)->second;
	break;
      }
      
    case UP:
      {
	return directionMap->find(UP)->second;
	break;
      }

    case DOWN:
      {
	return directionMap->find(DOWN)->second;
	break;
      }

    default:
      {
	return nullptr;
	break;
      }

    }
}

void Room::addPlayer(std::string playername)
{
  inhabitants->insert(playername);
}

void Room::removePlayer(std::string playername)
{
  inhabitants->erase(playername);
}



shared_ptr<Room> Room::getRoomInDirection(Direction direction)
{
  return directionMap->find(direction)->second;
}

shared_ptr<Thing> Room::getThingOfType(ThingType type) 
{
  shared_ptr<Thing> thing = nullptr;
  bool found = false;
  for(auto beg = things->begin(), end = things->end(); beg != end; ++beg )
    {
      //std::cout<<"getThingOfType"<<( (*beg)->thingtype)<<endl;
      //(thing) && (*beg)->thingtype == type ?  found = true: found = false;
      if((*beg)->thingtype == type)
	{
	  //std::cout<<"found match for "<<type<<endl;
	  thing = *beg;
	  
	}
    }
  //std::cout<<"match found is "<<thing->thingtype<<endl;
  return thing;
}

void Room::listThings()
{
  for(auto beg = things->begin(), end = things->end(); beg != end; ++beg)
    {
      //std::cout<<"Thing:: "<<Thing::thingTypeToNameMap.find(( (*beg)->thingtype))->second<<endl;
    }
}

shared_ptr<vector<shared_ptr<Thing> > > Room::getThings()
{
  return (things);
}

vector<shared_ptr<Player> > Room::getVisiblePlayers()
{
  vector<shared_ptr<Player> > visiblePlayers;
  for(auto itr = inhabitants->begin(); itr != inhabitants->end(); itr++)
  {
    string someone = *itr;
    shared_ptr<Player> player = Player::playerNameMap->find(someone)->second;
    if(player->role->stateStack->top()->isPlayerVisible())
      visiblePlayers.push_back(player);
  }
  return visiblePlayers;
}

bool Room::hasLight()
{
  return light;
}

void Room::toggleLight()
{
  light = !light;
}

bool Room::userPlayerPresent()
{
  return userPresent;
}

void Room::toggleUserPlayerPresent()
{
  userPresent = !userPresent;
}

void Room::setUserPlayerPresent()
{
  userPresent = true;
}


void Room::setDirectionsToWalls(int northwall)
{  
  northwall = northwall % TOP; //rand() % TOP;
  int northpos = 1;
  std::cout<<"Room::setting walls:: room is "<<id<<" begin"<<endl;
  //(*wallTypeDirMap)[lfrb[r]] = wnes[northpos];
  //(*wallTypeDirMap)[wnesud[northpos] ] = lfrbud[northwall];
  //(*dirWallTypeMap)[lfrbud[northwall] ] = wnesud[northpos];
  int pos = northpos;
  for(int i = northwall; i < northwall + TOP; i++, pos++)
    {
      int k = i % TOP;
      int j = pos % UP;
      //*(wallTypeDirMap)[lfrb[k]] = wnes[j];
      std::cout<<"setting dir = "<<dirNameMap.find(wnesud[j])->second<<" to walltype = "<<lfrbud[k]<<endl;
      (*wallTypeDirMap)[wnesud[j] ] = lfrbud[k];
      (*dirWallTypeMap)[ lfrbud[k] ] = wnesud[j];
    }
  (*wallTypeDirMap)[UP] = lfrbud[TOP];
  (*wallTypeDirMap)[DOWN] = lfrbud[BOTTOM];
  (*dirWallTypeMap)[TOP] = wnesud[UP];
  (*dirWallTypeMap)[BOTTOM] = wnesud[DOWN];
  std::cout<<"Room::setting walls;:end"<<endl;
  
}

void Room::addWall(DoorType doorType, shared_ptr<Door> door)
{
  door->addDisplay(id, doorType);

  (*wallDoorMap)[doorType] = door;

}

shared_ptr<Door> Room::getDoorInDirection(Direction dir)
{
  DoorType dtype = wallTypeDirMap->find(dir)->second;
  return wallDoorMap->find(dtype)->second;
}

