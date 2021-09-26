#include "Seeker.hpp"
#include <string>
#include <iostream>
using namespace std;

MAKE_ROLETYPE(Seeker)

Seeker::Seeker()
{
  std::cout<<"Seeker constructor"<<endl;
  stateStack = make_shared<stack<shared_ptr<RoleState> > >();
  std::cout<<"finished constructing Seeker"<<endl;
}

void Seeker::processCommand(shared_ptr<Command> cmd, shared_ptr<Player> player)
{
  //std::cout<<"Seeker::processing command"<<endl;
  //std::cout<<cmd->commandType<<endl;
  shared_ptr<RoleState> currentState = stateStack->top();
  currentState->update(cmd, stateStack, player);
  
  
  
}
