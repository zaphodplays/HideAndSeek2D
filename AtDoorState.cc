#include "AtDoorState.hpp"
#include <iostream>
using namespace std;

AtDoorState::AtDoorState()
{
  doorcenter = make_shared<Point2d>();
  originalCenter = make_shared<Point2d>();
  isDone = false;
  toPass = false;
  initAnimationSequence();
}

void AtDoorState::initState(shared_ptr<Point2d> originalCenter, int roomid, Direction direction, bool toPass)
{
  std::cout<<"AtDoorstate::initstate::begin"<<endl;
  this->originalCenter->x = originalCenter->x;
  this->originalCenter->y = originalCenter->y;
  
  this->setLocationID(roomid);
  this->direction = direction;
  setDirection(direction);
  this->toPass = toPass;
  std::cout<<"AtDoorState::initState::end"<<endl;
}


shared_ptr<RoleState> AtDoorState::getRoleState()
{
  return shared_from_this();
}

std::string AtDoorState::printState()
{
  std::cout<<"AtDoorState::printState()"<<endl;
  std::string print = "AtDoorState in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  std::cout<<"AtDoorState::printState() end"<<endl;
  return print;
}

void AtDoorState::displayState(Engine *engine, shared_ptr<Player> player)
{
  sequence->display(engine);
}




void AtDoorState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {
    case CONTINUE:
      {
	      SequenceState::update(cmd, stateStack, player);
	      passThrough(player);
	      isDone = true;
	      toPass = false;
	      break;
      }
    default:
      {
	      std::cout<<"command logic unimplemented"<<endl;
	      break;
      }

    }
    
}

void AtDoorState::passThrough(shared_ptr<Player> player)
{  	
  std::cout<<"AtDoorState::passThrough"<<endl;
  shared_ptr<Room> currentLocation = Room::roomIDMap->find(getLocationID())->second;
  shared_ptr<vector<Direction> > v = currentLocation->allowedDirections;
  if(!v)
    std::cout<<"AtDoorState::passThrough:: v is null";
  if(toPass && !v->empty() && find(v->begin(), v->end(), direction) != v->end() )
  {
      
    shared_ptr<Room> newLocation = currentLocation->move(direction);
    if(newLocation->getID() != currentLocation->getID())
    {
      setLocationID(newLocation->getID());
      currentLocation->removePlayer(player->getName());
      newLocation->addPlayer(player->getName());
      setDirection(Room::dirPairsMap.find(direction)->second );
      shared_ptr<Point2d> playerCenter = player->getCenter();
      player->shiftDisplay(doorcenter->x - playerCenter->x , doorcenter->y - playerCenter->y);
  
    }
  }
  std::cout<<"AtDoorState::end of passThrough"<<endl;

}

void AtDoorState::setDirection(Direction dir)
{
  this->direction = dir;
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  DoorType doorType = location->wallTypeDirMap->find(dir)->second;
  shared_ptr<Door> door = location->wallDoorMap->find(doorType)->second;
  doorcenter->x = (door->getCenter(getLocationID()))->x;
  doorcenter->y = (door->getCenter(getLocationID()))->y;
  
}


void AtDoorState::initAnimationSequence()
{
	sequence = initStandingAnimationSequence();
}

shared_ptr<AnimationSequence> AtDoorState::initStandingAnimationSequence()
  {
    shared_ptr<AnimationSequence> standingseq = make_shared<AnimationSequence>();

    
    return standingseq;
  }
