#include "UserPlayer.hpp"
#include <iostream>
using namespace std;

MAKE_PLAYERTYPE(UserPlayer)

UserPlayer::UserPlayer()
{
  commandParser = make_shared<CommandParser>();
  std::cout<<"finished constructing user player"<<endl;
}



shared_ptr<Command> UserPlayer::getCommand()
{
  const std::string continu = "continu";
  std::string input = continu;
  std::string c = "";
  std::string hello = "HELLO!!";
  //std::cout<<"hello is "<<hello<<endl;
  if(engine)
    {
      //std::cout<<"engine not null"<<endl;
      //engine->drawText(hello.c_str(), 100, 200);
      // while(engine->isUserTyping())
      //{
      //  engine->drawText(hello.c_str(), 100, 200);
      //}
      
      if(!engine->isUserTyping())
	{
	  input = engine->getPlayerInputText();
	  engine->resetInput();
	  	  
	}
      else 
	{
	  c = engine->getPlayerInputText();
	  if(c != "")
	    engine->drawText(c.c_str(), 300, 490);
	}
             
    }
  else
    {
      //std::cout<<"engine null"<<endl;
      getline(std::cin, input);
    }
  //getline(std::cin, input);
  //std::cin>>input;
  //std::cout<<"player "<<getName()<<endl;
  input.empty() ? input = continu : input = input + "";
  //std::cout<<"input is "<<input<<endl;
  shared_ptr<Command> cmd =  commandParser->getCommand(input);
  input = continu;
  return cmd;
  
}





void UserPlayer::processCommand(shared_ptr<Command> cmd)
{
  //std::cout<<"processing player "<<getName()<<endl;          
  //shared_ptr<Room> oldLocation = this->role->stateStack->top()->location;
  this->role->processCommand(cmd, shared_from_this());
  //shared_ptr<Room> newLocation = this->role->stateStack->top()->location;
  /** if(oldLocation->getID() != newLocation->getID())
    {
      oldLocation->toggleUserPlayerPresent();
      newLocation->toggleUserPlayerPresent();
      }**/
}

bool UserPlayer::isAI()
{
  return false;
}


