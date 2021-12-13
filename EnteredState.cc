#include "EnteredState.hpp"
#include "MovingState.hpp"
#include "AtDoorState.hpp"
#include <iostream>
using namespace std;

EnteredState::AllowedCmds EnteredState::allowedCommands = initAllowedCmds();;
EnteredState::EnteredStatePersonalityCommandMap EnteredState::epcMap = initEPCMap();

EnteredState::EnteredState(shared_ptr<Player> player)
{
  std::cout<<"constructing entered state"<<endl;
  this->player = player;
	initAnimationSequence();
}

shared_ptr<vector<int> > EnteredState::getWeights(AIPersonalityType personality) 
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = epcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > EnteredState::getAllowedCommands()
{
  return EnteredState::allowedCommands;
}

std::string EnteredState::printState()
{
  std::string print = " in room ";
  //std::cout<<"EnteredState::printState()";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + location->getName();
  return print;
}




void EnteredState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  switch(cmd->commandType)
    {
	case FOUND:
	{
		std::cout<<player->getName()<<" has been FOUND"<<endl;	
		shared_ptr<RoleState> foundState = make_shared<FoundState>(player);
		foundState->setLocationID(this->getLocationID());
		stateStack->push(foundState);
		break;
		
	}
    case MOVE:
      {
	    //std::cout<<player->getName()<<" in MOVE case"<<endl;
	    shared_ptr<RoleState> currentState = stateStack->top();
	
	    shared_ptr<Room> currentLocation = Room::roomIDMap->find(currentState->getLocationID())->second;
	    shared_ptr<vector<Direction> > v = currentLocation->allowedDirections;
	    if(!v->empty() && find(v->begin(), v->end(), cmd->dir) != v->end() )
	    {
	    
	      shared_ptr<Room> newLocation = currentLocation->move(cmd->dir);
	      if(newLocation->getID() != currentLocation->getID())
	      {
		      shared_ptr<Door> door = currentLocation->getDoorInDirection(cmd->dir);
		      shared_ptr<Point2d> doorcenter = door->getCenter(getLocationID());
		      //std::cout<<"door center is x = "<<doorcenter->x<<" , y = "<<doorcenter->y<<endl;
		      shared_ptr<Point2d> origplayercenter = make_shared<Point2d>();
		      origplayercenter->set(player->getCenter()->x, player->getCenter()->y);
		      shared_ptr<MovingState> moveToDoor = make_shared<MovingState>(player);
		      moveToDoor->initState(currentLocation->getID(), doorcenter, origplayercenter);
		      moveToDoor->setLocationID(currentLocation->getID());
		      moveToDoor->setSequence(1);

		      shared_ptr<AtDoorState> atDoor = make_shared<AtDoorState>();
		      atDoor->initState(origplayercenter, currentLocation->getID(), cmd->dir, true);
		      atDoor->setLocationID(currentLocation->getID());
		      atDoor->setSequence(2);

		/**shared_ptr<AtDoorState> atDoor2 = make_shared<AtDoorState>();
		atDoor->initState(origplayercenter, newLocation->getID(), Room::dirPairsMap.find(cmd->dir)->second, false);
		atDoor2->setSequence(3);**/
		
		      shared_ptr<Point2d> doorcenter2 = door->getCenter(newLocation->getID());
		      shared_ptr<MovingState> moveToRoom = make_shared<MovingState>(player);
		      moveToRoom->initState(newLocation->getID(), origplayercenter, doorcenter2);
		      moveToRoom->setLocationID(newLocation->getID());
		      moveToRoom->setSequence(3);

		      shared_ptr<EnteredState> enteredState = make_shared<EnteredState>(player);
		      enteredState->setLocationID(newLocation->getID());

		      moveToDoor->setNextState(atDoor);
		      //atDoor->setNextState(atDoor2);
		      atDoor->setNextState(moveToRoom);
		      moveToRoom->setEndState(enteredState);
		
		//currentLocation->removePlayer(player->getName());
		//newLocation->addPlayer(player->getName());
	         
		//shared_ptr<MovingToDoorState> movingToDoorState = make_shared<MovingToDoorState>();
		//movingToDoorState->addDoorWithRooms(
		//newstate->setLocationID(newLocation->getID());
		      stateStack->pop();
		      stateStack->push(moveToDoor);
		      //std::cout<<"finished adding sequence states"<<endl;
	      }
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
	 
	  thing->addPlayer(player->getName());
	
	  stateStack->push(hiddenState);
	  player->setPlayerDisplay(HIDDEN);
	  break;
	}
      case JUMP:
	{
	  //std::cout<<player->getName()<<" REALLY !! YOU WANT TO JUMP ??"<<endl;
	  shared_ptr<JumpingState> jumpState = make_shared<JumpingState>(player);
	  jumpState->setLocationID(stateStack->top()->getLocationID());
      int shiftx = sequence->getCenter()->x - jumpState->sequence->getCenter()->x;
      int shifty = sequence->getCenter()->y - jumpState->sequence->getCenter()->y;
    //jumpState->sequence->shiftDisplays(shiftx, shifty);
	  //std::cout<<"JUMP::location id is "<<getLocationID()<<endl;
	  //std::cout<<"JUMP::location is "<<Room::roomIDMap->find(getLocationID())->second->getName()<<endl;
	  stateStack->push(jumpState);
	  player->setPlayerDisplay(JUMPING);
	  break;
	}
      case UNHIDE:
	{
	  //CAN'T UNHIDE
	  //std::cout<<"can't unhide in Entered State"<<endl;
	  break;
	}
	
	
      case INVALID:
	{
	  break;
	}
    case CONTINUE:
      {
	      break;
      }
      default:
      {
	      std::cout<<"command logic unimplemented"<<endl;
      }

    }
    
}


void EnteredState::initAnimationSequence()
{
	sequence = initStandingAnimationSequence();
}

shared_ptr<AnimationSequence> EnteredState::initStandingAnimationSequence()
  {
    shared_ptr<AnimationSequence> standingseq = make_shared<AnimationSequence>();
  
    shared_ptr<DisplayObject> standingWithHandsUp = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);
    
    shared_ptr<DisplayObject> standingWithHandsDown = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);
    
    standingseq->addImage(standingWithHandsUp);
    standingseq->addImage(standingWithHandsDown);
    return standingseq;
  }