#include "HiddenState.hpp"
#include <iostream>
using namespace std;

HiddenState::AllowedCmds HiddenState::allowedCommands = initAllowedCmds();
HiddenState::HiddenStatePersonalityCommandMap HiddenState::hpcMap = initHPCMap();

HiddenState::HiddenState(shared_ptr<Player> player, shared_ptr<Thing> thing)
{
  this->player = player;
  this->thing = thing;
  initAnimationSequence();
}

std::string HiddenState::printState()
{
  std::cout<<"HiddenState::printState"<<endl;
  std::string print = " in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print= print+ location->getName();
  print = print + " hiding in " + Thing::thingTypeToNameMap.find(thing->thingtype)->second; 
  return print;
}


void HiddenState::displayState(Engine *engine, shared_ptr<Player> player)
{
  std::cout<<player->getName()<<" is hiding"<<endl;
  sequence->display(engine);
}


void HiddenState::update(shared_ptr<Command> cmd, shared_ptr< stack< shared_ptr< RoleState> > > stateStack, shared_ptr<Player> player)
{

  //std::cout<<"HiddenState in room "<<Room::roomTypeMap.find(location->getRoomType())->second<<endl;
  switch(cmd->commandType)
    {
    case FOUND:
    {
      std::cout<<player->getName()<<" has been FOUND"<<endl;	
      shared_ptr<RoleState> foundState = make_shared<FoundState>(player);
      foundState->setLocationID(this->getLocationID());
      thing->removePlayer(player->getName());
      thing = nullptr;
      player = nullptr;
      stateStack->pop();
      stateStack->push(foundState);
      break;
      
    }
    case LOOK:
      {
	//std::cout<<"You are hiding in "<< thing->thingtype<<endl;
	      break;
      }
    case HIDE:
      {
	//std::cout<<"you are already hiding"<<endl;
	      break;
      }
    case PEEK:
      {
        shared_ptr<RoleState> currentState = stateStack->top();
        shared_ptr<PeekState> peekState = make_shared<PeekState>(thing);
        peekState->setLocationID(currentState->getLocationID());
     
        stateStack->push(peekState);
        break;
      }
    case UNHIDE:
      {
        
        thing->removePlayer(player->getName());
        thing = nullptr;
        player = nullptr;
        stateStack->pop();
	
	
	//std::cout<<"in room "<<Room::roomTypeMap.find(location->getRoomType())->second<<endl;
       	break;
      }
    case CONTINUE:
    {
      break;
    }
    case INVALID:
      {
	break;
      }
    default:
      {
	//std::cout<<cmd->commandType<<" not implemented"<<endl;
	break;
      }
      
    }
  
}

shared_ptr<vector<int> > HiddenState::getWeights(AIPersonalityType personality)
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = hpcMap.find(personality)->second;
  return weights;
}


shared_ptr<vector<CommandType> > HiddenState::getAllowedCommands()
{
  return HiddenState::allowedCommands;
}

void HiddenState::initAnimationSequence()
{
  sequence = make_shared<AnimationSequence>();
  shared_ptr<DisplayObject> hidden = make_shared<DisplayObject>(TRANSPARENT, player->getCenter()->x, player->getCenter()->y);
  sequence->addImage(hidden);
}
