#include "SeekState.hpp"
#include "EnteredState.hpp"
#include "HiddenState.hpp"
#include <iostream>
using namespace std;


SeekState::AllowedCmds SeekState::allowedCommands = initAllowedCmds();;
SeekState::SeekStatePersonalityCommandMap SeekState::spcMap = initSPCMap();

SeekState::SeekState(shared_ptr<Player> player)
{
  isUP = false;
  this->player = player;
  initAnimationSequence();
}

SeekState::~SeekState()
{
  std::cout<<"SeekState getting destroyed: isUP "<<isUP<<endl;
}

void SeekState::initAnimationSequence()
{
  sequence = initSeekAnimationSequence();
}

shared_ptr<vector<int> > SeekState::getWeights(AIPersonalityType personality) 
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = spcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > SeekState::getAllowedCommands()
{
  return SeekState::allowedCommands;
}

std::string SeekState::printState()
{
  //std::cout<<"in seek print state"<<endl;
  std::string print = "Seeking in room ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  //std::cout<<"end of seek print state"<<endl;
  return print;
}


void SeekState::displayState(Engine *engine, shared_ptr<Player> player)
{
  
  sequence->display(engine);
    
}





void SeekState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {

	
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
	    shared_ptr<RoleState> newstate = make_shared<SeekState>(player);
	    if(newLocation->getID() != currentLocation->getID())
              {
                currentLocation->removePlayer(player->getName());
                newLocation->addPlayer(player->getName());
              }
	    newstate->setLocationID(newLocation->getID());
	    
	   
	    stateStack->push(newstate);
	    
	  }
	break;
      }
	  
      case LOOK:
	{
	  
	  //std::cout<<"LOOK: "<<endl;
	  shared_ptr<Room> room = Room::roomIDMap->find(stateStack->top()->getLocationID())->second;
	  //std::cout<<"room is "<<Room::roomTypeMap.find(room->getRoomType())->second<<endl;
	  room->listThings();
	  break;
	}
      case HIDE:
	{
	  
	  //std::cout<<"in HIDE case"<<endl;
	  shared_ptr<Thing> thing = Room::roomIDMap->find(getLocationID())->second->getThingOfType(cmd->thingType);
	  if(thing == nullptr)
	  {
		   cout<<"thing to hide cannot be null"<<endl;
		   break;
	  }
	  	
	  shared_ptr<HiddenState> hiddenState = make_shared<HiddenState>(player, thing);
	  
	  hiddenState->setLocationID(stateStack->top()->getLocationID());
	  //std::cout<<"in room"<<Room::roomTypeMap.find(this->location->getRoomType())->second<<endl;
	  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
	  
	  
	  stateStack->push(hiddenState);
	
	  break;
	}
      case JUMP:
	{
	  //std::cout<<player->getName()<<" REALLY !! YOU WANT TO JUMP ??"<<endl;
	  
	  break;
	}
	case CHECK:
	{
		std::cout<<"SEEKER going to check"<<endl;
		
	  	
	  	//std::cout<<"in room"<<Room::roomTypeMap.find(this->location->getRoomType())->second<<endl;
	  	shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
	  	shared_ptr<Thing> thing = location->getThingOfType(cmd->thingType);
		if(thing == nullptr)
	  {
		   cout<<"thing to hide cannot be null"<<endl;
		   break;
	  }
		if(thing->isEmpty())
		{

			cout<<player->getName()<<" checked "<<thing->getName()<<" found nothing"<<endl;
			break;
		}
		vector<std::string> players = thing->seek();
		vector<std::string>::iterator pitor = players.begin();
		while(pitor != players.end())
		{
			std::string pname = player->getName();
			if(pname.compare(*pitor) == 0)
				continue;
			shared_ptr<Player> someone = Player::playerNameMap->find(*pitor)->second;
			shared_ptr<Command> foundCommand = make_shared<Command>();
			foundCommand->commandType = FOUND;
			someone->processCommand(foundCommand);
			
			pitor++;
		}
		
	}
     
      case INVALID:
	{
	  break;
	}
      default:
      {
		shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
		

		for(shared_ptr<Player> someone : location->getVisiblePlayers())
		{
			if(player->getName().compare(someone->getName()) == 0  )
				continue;
			cout<<"FOUND hider "<<someone->getName()<<endl;
			shared_ptr<Command> fcmd = make_shared<Command>();
			fcmd->commandType = FOUND;
			someone->processCommand(fcmd);
		}
		
		break;
      }

    }
    
}

shared_ptr<AnimationSequence> SeekState::initSeekAnimationSequence()
{
  std::string filename = player->getFilename();
  shared_ptr<AnimationSequence> jumpseq = make_shared<AnimationSequence>();
  
  shared_ptr<DisplayObject> jump_down = make_shared<DisplayObject>(filename, player->getCenter()->x, player->getCenter()->y);
  shared_ptr<DisplayObject> jump_up = make_shared<DisplayObject>(filename, player->getCenter()->x, player->getCenter()->y);
  
  jumpseq->addImage(jump_up);
  jumpseq->addImage(jump_down);
  return jumpseq;
}


