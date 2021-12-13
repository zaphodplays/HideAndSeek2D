#include "JumpingState.hpp"
#include "EnteredState.hpp"
#include "HiddenState.hpp"
#include <iostream>
using namespace std;


JumpingState::AllowedCmds JumpingState::allowedCommands = initAllowedCmds();;
JumpingState::JumpingStatePersonalityCommandMap JumpingState::jpcMap = initJPCMap();

JumpingState::JumpingState(shared_ptr<Player> player)
{
  isUP = false;
  this->player = player;
  initAnimationSequence();
}

JumpingState::~JumpingState()
{
  std::cout<<"JumpingState getting destroyed: isUP "<<isUP<<endl;
}

void JumpingState::initAnimationSequence()
{
  sequence = initJumpAnimationSequence();
}

shared_ptr<vector<int> > JumpingState::getWeights(AIPersonalityType personality) 
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = jpcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > JumpingState::getAllowedCommands()
{
  return JumpingState::allowedCommands;
}

std::string JumpingState::printState()
{
  //std::cout<<"in jump print state"<<endl;
  std::string print = "Jumping in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  //std::cout<<"end of jump print state"<<endl;
  return print;
}


void JumpingState::displayState(Engine *engine, shared_ptr<Player> player)
{
  
  sequence->display(engine);
    
}

void JumpingState::stopJumping(shared_ptr<Player> player)
{
  if(isUP)
    {
      player->shiftDisplay(0, 20); 
    }
  isUP = false;
}



void JumpingState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {
	
	case FOUND:
    {
      std::cout<<player->getName()<<" has been FOUND"<<endl;	
      shared_ptr<RoleState> foundState = make_shared<FoundState>(player);
      foundState->setLocationID(this->getLocationID());
      
      stateStack->pop();
      stateStack->push(foundState);
      break;
      
    }
    case MOVE:
      {
	//stopJumping(player);
	//std::cout<<"in MOVE case"<<endl;
	shared_ptr<RoleState> currentState = stateStack->top();
	
	shared_ptr<Room> currentLocation = Room::roomIDMap->find(currentState->getLocationID())->second;
	shared_ptr<vector<Direction> > v = currentLocation->allowedDirections;
	if(!v->empty() && find(v->begin(), v->end(), cmd->dir) != v->end() )
	  {
	    
	    shared_ptr<Room> newLocation = currentLocation->move(cmd->dir);
	    shared_ptr<RoleState> newstate = make_shared<EnteredState>(player);
	    if(newLocation->getID() != currentLocation->getID())
              {
                currentLocation->removePlayer(player->getName());
                newLocation->addPlayer(player->getName());
              }
	    newstate->setLocationID(newLocation->getID());
	    stopJumping(player);
	    stateStack->pop();
	    stateStack->push(newstate);
	    
	  }
	break;
      }
	  
      case LOOK:
	{
	  stopJumping(player);
	  //std::cout<<"LOOK: "<<endl;
	  shared_ptr<Room> room = Room::roomIDMap->find(stateStack->top()->getLocationID())->second;
	  //std::cout<<"room is "<<Room::roomTypeMap.find(room->getRoomType())->second<<endl;
	  room->listThings();
	  break;
	}
      case HIDE:
	{
	  stopJumping(player);
	  
	  //std::cout<<"in HIDE case"<<endl;
	  
	  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
	  shared_ptr<Thing> thing =  location->getThingOfType(cmd->thingType);
	  shared_ptr<HiddenState> hiddenState = make_shared<HiddenState>(player, thing);
	  hiddenState->setLocationID(location->getID());
	  //std::cout<<"in room"<<Room::roomTypeMap.find(this->location->getRoomType())->second<<endl;
	  player->setPlayerDisplay(HIDDEN);
	 
	  stateStack->pop();
	  stateStack->push(hiddenState);
	
	  break;
	}
      case JUMP:
	{
	  std::cout<<"YES YES you are already jumping"<<endl;
	  break;
	}
	case STOP:
	{
		stopJumping(player);
		stateStack->pop();
		break;
	}
      case UNHIDE:
	{
	  //CAN'T UNHIDE
	  std::cout<<"can't unhide in Jumping State"<<endl;
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

shared_ptr<AnimationSequence> JumpingState::initJumpAnimationSequence()
{
  std::string filename = player->getFilename();
  shared_ptr<AnimationSequence> jumpseq = make_shared<AnimationSequence>();
  
  shared_ptr<DisplayObject> jump_down = make_shared<DisplayObject>(filename, player->getCenter()->x, player->getCenter()->y);
  shared_ptr<DisplayObject> jump_up = make_shared<DisplayObject>(filename, player->getCenter()->x, player->getCenter()->y-40);
  for(int i = 0; i < 100; i++)
	jumpseq->addImage(jump_up);	
  for(int j = 0; j < 100; j++)
  	jumpseq->addImage(jump_down);
  return jumpseq;
}


