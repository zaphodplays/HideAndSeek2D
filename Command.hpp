#ifndef _COMMAND_H
#define _COMMAND_H
#include <string>
#include <map>
#include "Enums.hpp"
#include <iostream>
using namespace std;



class Command {
  
 public:

  Command(){ };


  RELATION prep;

  ThingType thingType;

  Direction dir;

  shared_ptr<Command> getCommandOfType(CommandType cmdType);

    
public:
  typedef map<const std::string, CommandType> enumMap;
  static enumMap strenum_map;

  

 public:
  CommandType commandType;

  static const std::string continu;
  static const std::string list;
  static const std::string look;
  static const std::string lights;
  static const std::string hide;
  static const std::string unhide;
  static const std::string peek;
  static const std::string run;
  static const std::string check;
  static const std::string move;
  static const std::string jump;
  static const std::string stop;
    

private:
  static enumMap initMap() {
    enumMap someMap;
    someMap[continu] = CONTINUE;
    someMap[list] = LIST;
    someMap[look] = LOOK;
    someMap[lights] = LIGHTS;
    someMap[hide] = HIDE;
    someMap[unhide] = UNHIDE;
    someMap[jump] = JUMP;
    someMap[stop] = STOP;
    someMap[peek] = PEEK;
    someMap[run] = RUN;
    someMap[check] = CHECK;
    someMap[move] = MOVE;
    return someMap;
  }
  /**
  static shared_ptr<Command> buildAICommand(CommandType commandType, shared_ptr<RoleState> currentState)
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
	  cmd->prep = currentState->location->hasLight() ? OFF : ON;
	  break;
	}

      case HIDE:
	{
	  int thingsize = currentState->location->things->size();
	  int rnum = rand() % (thingsize);
	  std::cout<<"HIDE::rnum = "<<rnum<<endl;
	  shared_ptr<Thing> thing = (*(currentState->location->things))[rnum - 1];
	  shared_ptr<vector<RELATION>  > relations = thing->getAllowedRelationsForCmdType(commandType);
	  int relnum = rand() % (relations->size());
	  std::cout<<"relnum = "<<relnum<<endl;
	  cmd->prep = (*relations)[relnum - 1);
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
	  int rnum = rand() % (currentState->location->allowedDirections->size());
	  std::cout<<"MOVE::rnum = "<<rnum<<endl;
	  cmd->dir = (*(currentState->location->allowedDirections))[rnum - 1];
	  break;
	}
	
      default:
	{
	  break;
	}
      
      }
  return cmd;
  } 
  
  **/
};
#endif
