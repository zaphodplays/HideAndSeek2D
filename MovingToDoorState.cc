#include "MovingToDoorState.hpp"
#include <iostream>
using namespace std;



shared_ptr<vector<int> > MovingToDoorState::getWeights(AIPersonalityType personality) 
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  
  return weights;
}

shared_ptr<vector<CommandType> > MovingToDoorState::getAllowedCommands()
{
  return MovingToDoorState::allowedCommands;
}

shared_ptr MovingToDoorState::getRoleState()
{
  return shared_from_this();
}

std::string MovingToDoorState::printState()
{
  std::string print = " in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + Room::roomTypeMap.find(location->getRoomType())->second;
  return print;
}


void MovingToDoorState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {
    case PROGRESS:
      {
	if(hasReachedDoor)
	  {
	    //return AtDoorState
	  }
	else
	  {
	    //keep moving
	    keepMoving(player);
	    
	    
	  }
	break;
      }
    default:
      {
	std::cout<<"command logic unimplemented"<<endl;
	break;
      }

    }
    
}

bool MovingToDoorState::hasReachedDoor(shared_ptr<Point2d> plocation)
{
  return ((*plocation == *doorcenter));
}

void MovingToDoorState::keepMoving(shared_ptr<Player> player)
{
  // Check if element exists in vector
  vector<shared_ptr<Point2d> >::iterator it = std::find(linepoints->begin(), linepoints->end(), plocation);

  if (it != linepoints->end())
    {
      int index = std::distance(linepoints->begin(), it);
      shared_ptr<Point2d> center = player->getCenter();
      shared_ptr<Point2d> nextpoint = *linepoints[index + 1];
      player->shift(nextpoint->x - center->x, nextpoint->y - center->y);
    }
  else
    {
      std::std::cout << "Element Not Found" << std::endl;
    }


}

void MovingToDoorState::setDirection(Direction dir, shared_ptr<Point2d> originalPlayerPosition)
{
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  DoorType doorType = wallTypeDirMap->find(dir)->second;
  shared_ptr<Door> door = walls->find(doorType)->second;
  shared_ptr<Polygon> doorgon = doorTypeMap.find(doorType)->second;
  doorcenter = doorgon->getCenter();
  originalPosition->set(originalPlayerPosition->x, originalPlayerPositon->y);
  this->dir = dir;
}
