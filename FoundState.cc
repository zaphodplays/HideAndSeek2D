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
  std::cout<<"in jump print state"<<endl;
  std::string print = "Found in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  std::cout<<"end of jump print state"<<endl;
  return print;
}


void FoundState::displayState(Engine *engine, shared_ptr<Player> player)
{
  
  sequence->display(engine);
    
}





void FoundState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {
    
	  
      case LOOK:
	{
	  
	  //std::cout<<"LOOK: "<<endl;
	  shared_ptr<Room> room = Room::roomIDMap->find(stateStack->top()->getLocationID())->second;
	  //std::cout<<"room is "<<Room::roomTypeMap.find(room->getRoomType())->second<<endl;
	  room->listThings();
	  break;
	}
    
      case JUMP:
	{
	  std::cout<<player->getName()<<" REALLY !! YOU WANT TO JUMP ??"<<endl;
	  shared_ptr<JumpingState> jumpState = make_shared<JumpingState>(player);
	  jumpState->setLocationID(stateStack->top()->getLocationID());
    int shiftx = sequence->getCenter()->x - jumpState->sequence->getCenter()->x;
    int shifty = sequence->getCenter()->y - jumpState->sequence->getCenter()->y;
    //jumpState->sequence->shiftDisplays(shiftx, shifty);
	  std::cout<<"JUMP::location id is "<<getLocationID()<<endl;
	  std::cout<<"JUMP::location is "<<Room::roomIDMap->find(getLocationID())->second->getName()<<endl;
	  stateStack->push(jumpState);
	  player->setPlayerDisplay(JUMPING);
	  break;
	}
	
    
      case INVALID:
        {
        break;
        }
      default:
      {
	    std::cout<<"command logic unimplemented"<<endl;
      }

    }
    
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


