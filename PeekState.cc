#include "PeekState.hpp"
#include "Thing.hpp"
#include <iostream>
using namespace std;

PeekState::AllowedCmds PeekState::allowedCommands = initAllowedCmds();
PeekState::PeekStatePersonalityCommandMap PeekState::ppcMap = initPPCMap();
std::string PeekState::EYES = "eyes.png";
std::string PeekState::NOEYES = "NOEYES.png";

PeekState::PeekState(shared_ptr<Thing> thing)
{
  this->thing = thing;
  initAnimationSequence();
}

shared_ptr<Thing> PeekState::getThing()
{
  return thing;
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
  print = print + " peeking from  " + thing->getName();
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
 case FOUND:
    {
      std::cout<<player->getName()<<" has been FOUND"<<endl;	
      shared_ptr<RoleState> foundState = make_shared<FoundState>(player);
      foundState->setLocationID(this->getLocationID());
      thing->removePlayer(player->getName());
      thing = nullptr;
      stateStack->pop();
      stateStack->pop();
      stateStack->push(foundState);
      break;
      
    }
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
     thing = nullptr;
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
  int x = rand()%50;
  int y = rand()%50;
  shared_ptr<DisplayObject> eyes = make_shared<DisplayObject>(EYES, thing->getCenter()->x+ x, thing->getCenter()->y+ y);
  
  shared_ptr<DisplayObject> noeyes = make_shared<DisplayObject>(NOEYES, thing->getCenter()->x+ x, thing->getCenter()->y+ y);
  for(int i = 0; i < 100; i++)
    peekseq->addImage(eyes);
  for(int i = 0; i < 100; i ++)
    peekseq->addImage(noeyes);

  return peekseq;
}

bool PeekState::isPlayerVisible()
{
  return false;
}


