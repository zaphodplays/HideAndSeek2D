#ifndef _CMD_PARSER_H
#define _CMD_PARSER_H
#include <iostream>
#include <memory>
#include <map>
#include "Enums.hpp"
#include "Room.hpp"
#include "Thing.hpp"
#include "Command.hpp"



using namespace std;

class CommandParser {
  
 public:
  //Command command;

  CommandParser();
  
  shared_ptr<Command> getCommand(const std::string &input);

 private:
  map<std::string, shared_ptr<Command> > commandMap;
 
};
#endif

