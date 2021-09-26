#include "RoleState.hpp"
#include <iostream>
using namespace std;

RoleState::RoleState()
{
  std::cout<<"constructing RoleState"<<endl;
  gameTimeType = NORMALTIME;
  std::cout<<"finished constructing RoleState"<<endl;
  
}

void RoleState::initAnimationSequence()
{
  sequence = make_shared<AnimationSequence>();
  
}

void RoleState::displayState(Engine *engine, shared_ptr<Player> player)
{
  //player->displayState();
  sequence->display(engine);
}

GameTimeType RoleState::getGameTimeType()
{
  return gameTimeType;
}

shared_ptr<Command> RoleState::getAICommand(AIPersonalityType personality)
{
  shared_ptr<vector<int> > weights = getWeights(personality); 
  int sum = (*weights)[weights->size() - 1];
  int rnum = rand() % (sum);
                                                                                                                                                                
  int n = weights->size()/2;
  int res = rnum;
  int idx = 0;
  for(int i = 0; i < weights->size(); i++)
    {
      //std::cout<<"weight = "<<(*weights)[i]<<endl;
      res = rnum - (*weights)[i];
      if(res <= 0)
	{
	  idx = i;
	  break;
	}
    }
  //std::cout<<"idx is "<<idx<<endl;
  shared_ptr<vector<CommandType> > cmds = getAllowedCommands();
  std::cout<<"command type is "<<((*cmds)[idx])<<endl;
  shared_ptr<Command> cmd = buildAICommand( ((*cmds)[idx]));

  return cmd;
}

shared_ptr<Command> RoleState::buildAICommand(CommandType commandType)
  {
    shared_ptr<Command> cmd = make_shared<Command>();
    cmd->commandType = commandType;
    switch(commandType)
      {
      case LIST:
        {
          break;
        }

      case LOOK:
        {
          break;
        }

      case LIGHTS:
        {
	        shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
          cmd->prep = location->hasLight() ? OFF : ON;
          break;
        }

      case HIDE:
        {
	        shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
          int thingsize = location->things->size();
          int rnum = rand() % (thingsize);
          //std::cout<<"HIDE::rnum = "<<rnum<<endl;
	        rnum ? rnum = rnum * 1 : ++rnum;
          shared_ptr<Thing> thing = (*(location->things))[rnum ];
          shared_ptr<vector<RELATION>  > relations = thing->getAllowedRelationsForCmdType(commandType);
          int relnum = rand() % (relations->size());
          //std::cout<<"relnum = "<<relnum<<endl;
          cmd->prep = (*relations)[relnum ];
          cmd->thingType = thing->thingtype;
          break;
        }

      case UNHIDE:
        {
          break;
        }

      case PEEK:
        {
            break;
        }

      case RUN:
        {
          break;
        }

      case CHECK:
        {
          break;
        }

      case MOVE:
        {
	        shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
          int rnum = rand() % (location->allowedDirections->size());
	        if(rnum >= location->allowedDirections->size())
	          std::cout<<"WRONG!!!::MOVE::rnum = "<<rnum<<endl;
          cmd->dir = (*(location->allowedDirections))[rnum];
          break;
        }
      case CONTINUE:
	    {
	      break;
	    }

      default:
        {
          break;
        }

      }
  return cmd;
  }

void RoleState::setLocationID(int id)
{
  locationid = id;
}

int RoleState::getLocationID()
{
  return locationid;
}


