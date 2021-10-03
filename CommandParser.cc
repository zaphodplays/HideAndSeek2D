#include <vector>
#include <map>
#include "CommandParser.hpp"


shared_ptr<Command> CommandParser::getCommand(const std::string &input)
{
  std::cout<<"in commandparser"<<endl;
  size_t pos = -1;
  size_t start = -1;
  vector<string> parsedInput;
  do{
    start = ++pos;
    //std::cout<<"start is "<<start<<endl;
    pos = input.find(" ", start);
    std::string word = input.substr(start, pos-start);
    //std::cout<<"pos is "<<pos<<"word is "<<word<<endl;
    parsedInput.push_back(word);
    
  }while(pos != std::string::npos);
  std::cout<<"parsedInput size is "<<parsedInput.size()<<endl;
  
  std::string cname = parsedInput[0];
  std::cout<<"cname is "<<cname<<endl;
  std::string preposition;
  std::string target;
  int size = parsedInput.size();
  shared_ptr<Command> cmd;
  if(commandMap.find(cname) != commandMap.end())
    {
      cmd = commandMap.find(cname)->second;
      //cmd->thingType = CONTINUE;
    }
  else 
    {
      cmd = make_shared<Command>();
      cmd->commandType = INVALID;
      
    }
      
  std::cout<<"switching for "<<cname<<endl;
  switch(cmd->commandType)
    {
    case LIST:
      {
	break;
      }
    case SEEK:
    {
      break;
    }

    case LOOK:
      {
	//cmd->prep = parsedInput[1];
	break;
      }

    case LIGHTS:
      {
	cmd->prep = Thing::relMap.find(parsedInput[1])->second;
	break;
      }

    case HIDE:
      {
        if( (size == 3) && (Thing::relMap.find(parsedInput[1]) != Thing::relMap.end()) && (Thing::thingMap.find(parsedInput[2]) != Thing::thingMap.end()) )
          {
            cmd->prep = Thing::relMap.find(parsedInput[1])->second;
            ThingType thingType  = Thing::thingMap.find(parsedInput[2])->second;
            //std::cout<<"thingType for "<<parsedInput[2]<<" is "<<thingType<<endl;
            cmd->thingType = thingType;
            std::cout<<"thing:: thingtype is "<<(cmd->thingType)<<endl;
          }
        else if(size == 1)
        {
          cmd->thingType = NONE;  
        }
        else
          {
            cmd->commandType = INVALID;
          }
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
	// check a thing;
        if( (size == 2) && (Thing::relMap.find(parsedInput[1]) != Thing::relMap.end()) && (Thing::thingMap.find(parsedInput[2]) != Thing::thingMap.end()) )
          {
            
            ThingType thingType  = Thing::thingMap.find(parsedInput[1])->second;
            //std::cout<<"thingType for "<<parsedInput[2]<<" is "<<thingType<<endl;
            cmd->thingType = thingType;
            std::cout<<"thing:: thingtype is "<<(cmd->thingType)<<endl;
          }
        else if(size == 1)
        {
          cmd->thingType = NONE;  
        }
        else
          {
            cmd->commandType = INVALID;
          }
	      break;
      }

    case MOVE:
      {
        //move direction
        //std::cout<<"dir std::string = "<<parsedInput[1]<<endl;
        Direction tomove = Room::dirMap.find(parsedInput[1])->second;
        //std::cout<<"CmdParser::MOVE case:: dir = "<<tomove<<endl;
        cmd->dir = tomove;
        break;
      }
    case JUMP:
      {
        if( (size == 3) & (Thing::relMap.find(parsedInput[1]) != Thing::relMap.end()) && (Thing::thingMap.find(parsedInput[2]) != Thing::thingMap.end()) )
          {
            cmd->prep = Thing::relMap.find(parsedInput[1])->second;
            ThingType thingType  = Thing::thingMap.find(parsedInput[2])->second;
            //std::cout<<"thingType for "<<parsedInput[2]<<" is "<<thingType<<endl;                                                                                                           
            cmd->thingType = thingType;
          }
        else
          {
            cmd->thingType = NONE;
          }
        
        break;
      
      }
    case INVALID:
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

CommandParser::CommandParser()
{
  shared_ptr<Command> listCommand = make_shared<Command>();
  listCommand->commandType = LIST;

  shared_ptr<Command> lookCommand = make_shared<Command>();
  lookCommand->commandType = LOOK;

  shared_ptr<Command> lightsCommand = make_shared<Command>();
  lightsCommand->commandType = LIGHTS;

  shared_ptr<Command>hideCommand = make_shared<Command>();
  hideCommand->commandType = HIDE;

  shared_ptr<Command> unhideCommand = make_shared<Command>();
  unhideCommand->commandType = UNHIDE;

  shared_ptr<Command> peekCommand = make_shared<Command>();
  peekCommand->commandType = PEEK;

  shared_ptr<Command> runCommand = make_shared<Command>();
  runCommand->commandType = RUN;

  shared_ptr<Command> checkCommand = make_shared<Command>();
  checkCommand->commandType = CHECK;

  shared_ptr<Command> moveCommand = make_shared<Command>();
  moveCommand->commandType = MOVE;

  shared_ptr<Command> jumpCommand = make_shared<Command>();
  jumpCommand->commandType = JUMP;

  shared_ptr<Command> stopCommand = make_shared<Command>();
  stopCommand->commandType = STOP;

  shared_ptr<Command> continueCommand = make_shared<Command>();
  continueCommand->commandType = CONTINUE;

  commandMap[Command::continu] = continueCommand;
  commandMap[Command::list] =  listCommand;
  commandMap[Command::look] = lookCommand;
  commandMap[Command::lights] = lightsCommand;
  commandMap[Command::hide] = hideCommand;
  commandMap[Command::unhide] = unhideCommand;
  commandMap[Command::peek] = peekCommand;
  commandMap[Command::run] = runCommand;
  commandMap[Command::check] = checkCommand;
  commandMap[Command::move] = moveCommand;
  commandMap[Command::jump] = jumpCommand;
  commandMap[Command::stop] = stopCommand;

  

  
}

/**
int main()
{
  shared_ptr<Room> hall = make_shared<Room>();
  hall->setID(1);
  hall->setRoomType(CENTRALHALL);

  std::cout<<"hall roomtype "<<hall->getRoomType()<<endl;
  shared_ptr<Room> pg = make_shared<Room>();
  pg->setID(2);
  pg->setRoomType(PLAYGROUND);
  std::cout<<"playground roomtype "<<pg->getRoomType()<<endl;

  shared_ptr<Thing> chair = make_shared<Chair>();
  shared_ptr<Thing> tree = make_shared<Tree>();
  shared_ptr<Thing> chair1 = make_shared<Chair>();
  shared_ptr<Thing> tree1 = make_shared<Tree>();
  

  shared_ptr<Thing> chair2 = Thing::makeThing("Chair");
  shared_ptr<Thing> tree2 = Thing::makeThing("Tree");
  shared_ptr<Thing> chair3 = Thing::makeThing("Chair");
  shared_ptr<Thing> tree3 = Thing::makeThing("Tree");
  shared_ptr<Thing> chair4 = Thing::makeThing("Chair");
  shared_ptr<Thing> tree4 = Thing::makeThing("Tree");

  std::cout<<"type for thing is "<<chair2->thingtype<<endl;
  std::cout<<"type for thing is "<<tree2->thingtype<<endl;

  shared_ptr<Room> bedroom = make_shared<Room>();
  bedroom->setID(3);
  bedroom->setRoomType(BEDROOM);
  bedroom->things->push_back(chair2);
  bedroom->things->push_back(tree2);

  shared_ptr<Room> livingroom = make_shared<Room>();
  livingroom->setID(4);
  livingroom->setRoomType(LIVINGROOM);
  livingroom->things->push_back(chair3);
  livingroom->things->push_back(tree3);

  shared_ptr<Room> diningroom = make_shared<Room>();
  diningroom->setID(5);
  diningroom->setRoomType(DININGROOM);
  diningroom->things->push_back(chair4);
  diningroom->things->push_back(tree4);

  

  //shared_ptr<vector<shared_ptr<Thing> > > vec = make_shared<vector<shared_ptr<Thing> > >();
  //hall->things = vec;
  //vec->push_back(chair);
  shared_ptr<Player> player1 = make_shared<Player>();
  player1->setName("Cheeku");
  //player1->setLocation(hall);
  setRoomInDirection(NORTH, hall, pg);
  
  setRoomInDirection(SOUTH, hall, bedroom);
  setRoomInDirection(WEST, hall, livingroom);
  setRoomInDirection(EAST, hall, diningroom);
  
  hall->things->push_back(chair);
  hall->things->push_back(tree);
  pg->things->push_back(chair1);
  pg->things->push_back(tree1);
  
  //std::string s = "hide on tree";
  
  CommandParser parser;
  //shared_ptr<Command> newcommand = parser.getCommand(s);
  //std::cout<<"new command type is "<<(newcommand->commandType)<<endl;
  //std::cout<<"prep is "<<newcommand->prep<<endl;
  //std::cout<<"thing is "<<newcommand->thingType<<endl;

  std::string s2 = "move north";
  shared_ptr<Command> newcommand = parser.getCommand(s2);
  //std::cout<<"new command type is "<<(newcommand->commandType)<<endl;
  //std::cout<<"direction is "<<newcommand->dir<<endl;
  //std::cout<<"player's location is "<<player1->getLocation()->getRoomType()<<endl;
  //player1->setLocation(player1->getLocation()->move(Direction::SOUTH));
  //std::cout<<"player's new location si "<<player1->getLocation()->getRoomType()<<endl;

  //player1->setLocation(player1->getLocation()->move(NORTH));
  //std::cout<<"player's new location is "<<(player1->getLocation()->getRoomType())<<endl;

  shared_ptr<Role> seeker = make_shared<Seeker>();
  player1->role = seeker;
  shared_ptr<RoleState> state1 = make_shared<EnteredState>();
  state1->location = hall;
  seeker->stateStack->push(state1);

  player1->processCommand(newcommand);
  //std::cout<<"player's new location is "<<(player1->role->stateStack->top()->location->getRoomType())<<endl;

  std::string s3 = "move south";
  newcommand = parser.getCommand(s3);
  player1->processCommand(newcommand);
  //std::cout<<"player's new location is "<<(player1->role->stateStack->top()->location->getRoomType())<<endl;
  
  std::string s4 = "look";
  newcommand = parser.getCommand(s4);
  player1->processCommand(newcommand);

  std::string s5 = "hide behind tree";
  newcommand = parser.getCommand(s5);
  player1->processCommand(newcommand);

  std::string s6 = "look";
  newcommand = parser.getCommand(s6);
  player1->processCommand(newcommand);

  std::string s7 = "peek";
  newcommand = parser.getCommand(s7);
  player1->processCommand(newcommand);

  std::string s8 = "hide";
  newcommand = parser.getCommand(s8);
  player1->processCommand(newcommand);

  std::string s9 = "peek";
  newcommand = parser.getCommand(s9);
  player1->processCommand(newcommand);

  std::string s10 = "unhide";
  newcommand = parser.getCommand(s10);
  player1->processCommand(newcommand);
  
  std::string s11 = "look";
  newcommand = parser.getCommand(s11);
  player1->processCommand(newcommand);

  std::string s12 = "move west";
  newcommand = parser.getCommand(s12);
  player1->processCommand(newcommand);

  std::string s13 = "look";
  newcommand = parser.getCommand(s13);
  player1->processCommand(newcommand);

  std::string s14 = "hide in chair";
  newcommand = parser.getCommand(s14);
  player1->processCommand(newcommand);

  std::string s15 = "hide in tree";
  newcommand = parser.getCommand(s15);
  player1->processCommand(newcommand);

  std::string s16 = "peek";
  newcommand = parser.getCommand(s16);
  player1->processCommand(newcommand);

  std::string s17 = "unhide";
  newcommand = parser.getCommand(s17);
  player1->processCommand(newcommand);

  std::string s18 = "move east";
  newcommand = parser.getCommand(s18);
  player1->processCommand(newcommand);

  std::string s19 = "look";
  newcommand = parser.getCommand(s19);
  player1->processCommand(newcommand);
 
  
}

**/


