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

    shared_ptr<DisplayObject> standingWithHandsUp = make_shared<DisplayObject>();
    shared_ptr<Line> hand1 = make_shared<Line>();
    hand1->addPoints(347, 342, 364, 348);
    hand1->setColour(0x000000u);

    shared_ptr<Line> hand2 = make_shared<Line>();
    hand2->addPoints(379, 345, 394, 334);
    hand2->setColour(0x000000u);

    shared_ptr<Line> leg1 = make_shared<Line>();
    leg1->addPoints(365, 364, 359, 381);
    leg1->setColour(0x000000u);

    shared_ptr<Line> leg2 = make_shared<Line>();
    leg2->addPoints(375, 365, 383, 381);
    leg2->setColour(0x000000u);

    shared_ptr<Polygon> polygon = make_shared<Polygon>();
    polygon->addPoint2d(367,341);
    polygon->addPoint2d(377, 341);
    polygon->addPoint2d(384, 364);
    polygon->addPoint2d(359, 364);
    polygon->addPoint2d(367, 341);

    shared_ptr<Circle> circle = make_shared<Circle>();
    circle->addParameters(371,332, 10, 0x00ccbbu);

    shared_ptr<Circle> eye1 = make_shared<Circle>();
    eye1->addParameters(368,330, 2, 0x000000u);

    shared_ptr<Circle> eye2 = make_shared<Circle>();
    eye2->addParameters(375,330,2, 0x000000u);

    shared_ptr<Line> mouth = make_shared<Line>();
    mouth->addPoints(368,335, 374, 335);
    mouth->linecolour = 0x000000u;

    
    standingWithHandsUp->setCenter(polygon->getCenter()->x, polygon->getCenter()->y);
    

    shared_ptr<DisplayObject> standingWithHandsDown = make_shared<DisplayObject>();
    shared_ptr<Line> hp_hand1 = make_shared<Line>();
    hp_hand1->addPoints(347, 352, 364, 348);
    hp_hand1->setColour(0x000000u);

    shared_ptr<Line> hp_hand2 = make_shared<Line>();
    hp_hand2->addPoints(379, 345, 394, 354);
    hp_hand2->setColour(0x000000u);

    shared_ptr<Line> hp_leg1 = make_shared<Line>();
    hp_leg1->addPoints(365, 364, 359, 381);
    hp_leg1->setColour(0x000000u);

    shared_ptr<Line> hp_leg2 = make_shared<Line>();
    hp_leg2->addPoints(375, 365, 383, 381);
    hp_leg2->setColour(0x000000u);

    shared_ptr<Polygon> hp_polygon = make_shared<Polygon>();
    hp_polygon->addPoint2d(367,341);
    hp_polygon->addPoint2d(377, 341);
    hp_polygon->addPoint2d(384, 364);
    hp_polygon->addPoint2d(359, 364);
    hp_polygon->addPoint2d(367, 341);

    shared_ptr<Circle> hp_circle = make_shared<Circle>();
    hp_circle->addParameters(371,332, 10, 0x00ccbbu);
    
    shared_ptr<Circle> hp_eye1 = make_shared<Circle>();
    hp_eye1->addParameters(368,330, 2, 0x000000u);

    shared_ptr<Circle> hp_eye2 = make_shared<Circle>();
    hp_eye2->addParameters(375,330,2, 0x000000u);

    shared_ptr<Line> hp_mouth = make_shared<Line>();
    hp_mouth->addPoints(368,335, 374, 335);
    hp_mouth->linecolour = 0x000000u;

    
    standingWithHandsDown->setCenter(hp_polygon->getCenter()->x, hp_polygon->getCenter()->y);

    standingseq->addImage(standingWithHandsUp);
    standingseq->addImage(standingWithHandsDown);
    return standingseq;
  }
