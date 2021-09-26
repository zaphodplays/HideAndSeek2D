#ifndef _USERPLAYER_H
#define _USERPLAYER_H
#include "Player.hpp"
#include "CommandParser.hpp"
#include "Engine.h"

class UserPlayer : public Player
{
public:

   _PLAYERCLONE(UserPlayer)
  
  UserPlayer();

  

  virtual shared_ptr<Command> getCommand();
  virtual void processCommand(shared_ptr<Command> cmd);
  virtual bool isAI() override;
 
  // virtual void displayState();

private:
  shared_ptr<CommandParser> commandParser;
  

};
#endif
