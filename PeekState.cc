#include "PeekState.hpp"
#include "Thing.hpp"
#include <iostream>
using namespace std;

PeekState::AllowedCmds PeekState::allowedCommands = initAllowedCmds();
PeekState::PeekStatePersonalityCommandMap PeekState::ppcMap = initPPCMap();

PeekState::PeekState()
{
  initAnimationSequence();
}

shared_ptr<vector<int> > PeekState::getWeights(AIPersonalityType personality)
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = ppcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > PeekState::getAllowedCommands()
{
  return PeekState::allowedCommands;
}


std::string PeekState::printState()
{
  std::cout<<"PeekState::printState()"<<endl;
  std::string print = " in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print= print+ location->getName();
  print = print + " peeking from  " + Thing::thingTypeToNameMap.find(thing->thingtype)->second; 
  return print;
}


void PeekState::displayState(Engine *engine, shared_ptr<Player> player)
{
  sequence->display(engine);
}


void PeekState::update(shared_ptr<Command> cmd, shared_ptr< stack< shared_ptr< RoleState > > > stateStack, shared_ptr<Player> player)
{
  //std::cout<<"PEEKSTATE in room "<<Room::roomTypeMap.find(location->getRoomType())->second<<endl;
  switch(cmd->commandType)
{
 case LOOK:
   {
     std::cout<<"you are peeking"<<endl;
     shared_ptr<RoleState> currentState = stateStack->top();
     shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;

     std::cout<<"room is "<<location->getName()<<endl;
     break;
   }
 case HIDE:
   {
     std::cout<<"case HIDE"<<endl;
     stateStack->pop();
     break;
   }
 case UNHIDE:
   {
     stateStack->pop();
     stateStack->pop();
     break;
   }
 case INVALID:
   {
     break;
   }
 default:
   {
     //std::cout<<"peekstate:: cmdtype "<<cmd->commandType<<" not implemented"<<endl;
   }
}

}

void PeekState::initAnimationSequence()
{
  sequence = initPeekAnimationSequence();
}

shared_ptr<AnimationSequence> PeekState::initPeekAnimationSequence()
{
  shared_ptr<AnimationSequence> peekseq = make_shared<AnimationSequence>();
  shared_ptr<DisplayObject> peek1 = make_shared<DisplayObject>();
  shared_ptr<Circle> eye1 = make_shared<Circle>();
  eye1->addParameters(368,330, 2, 0x000000u);

  shared_ptr<Circle> eye2 = make_shared<Circle>();
  eye2->addParameters(375,330,2, 0x000000u);
  //replace with peeking image
  //peek1->addCircle(eye1);
  //peek1->addCircle(eye2);

  shared_ptr<DisplayObject> peek2 = make_shared<DisplayObject>();
  shared_ptr<Circle> eye12 = make_shared<Circle>();
  eye12->addParameters(368,330, 2, 0x005500u);

  shared_ptr<Circle> eye22 = make_shared<Circle>();
  eye22->addParameters(375,330,2, 0x005500u);
  //peek2->addCircle(eye12);
  //peek2->addCircle(eye22);
  
  peekseq->addImage(peek1);
  peekseq->addImage(peek2);
  return peekseq;
}


