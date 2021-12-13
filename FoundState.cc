#include "FoundState.hpp"
#include "EnteredState.hpp"
#include "HiddenState.hpp"
#include <iostream>
using namespace std;


FoundState::AllowedCmds FoundState::allowedCommands = initAllowedCmds();;
FoundState::FoundStatePersonalityCommandMap FoundState::jpcMap = initJPCMap();

FoundState::FoundState(shared_ptr<Player> player)
{
  isUP = false;
  this->player = player;
  initAnimationSequence();
}

FoundState::~FoundState()
{
  std::cout<<"FoundState getting destroyed: isUP "<<isUP<<endl;
}

void FoundState::initAnimationSequence()
{
  sequence = initFoundAnimationSequence();
}

shared_ptr<vector<int> > FoundState::getWeights(AIPersonalityType personality) 
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = jpcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > FoundState::getAllowedCommands()
{
  return FoundState::allowedCommands;
}

std::string FoundState::printState()
{
  //std::cout<<"in found print state"<<endl;
  std::string print = "Found in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  //std::cout<<"end of foundprint state"<<endl;
  return print;
}


void FoundState::displayState(Engine *engine, shared_ptr<Player> player)
{
  
  sequence->display(engine);
    
}





void FoundState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  
    
}

shared_ptr<AnimationSequence> FoundState::initFoundAnimationSequence()
{
  shared_ptr<AnimationSequence> standingseq = make_shared<AnimationSequence>();
  
    shared_ptr<DisplayObject> standingWithHandsUp = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);

    shared_ptr<DisplayObject> standingWithHandsDown = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);

    standingseq->addImage(standingWithHandsUp);
    standingseq->addImage(standingWithHandsDown);
    return standingseq;
}


