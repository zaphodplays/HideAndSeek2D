#include "Hider.hpp"
#include <iostream>
using namespace std;

MAKE_ROLETYPE(Hider)

Hider::Hider()
{
  stateStack = make_shared<stack<shared_ptr<RoleState> > >();
  std::cout<<"finished constructing hider"<<endl;
}

void Hider::processCommand(shared_ptr<Command> cmd, shared_ptr<Player> player)
{
  
  shared_ptr<RoleState> currentState = stateStack->top();
  std::cout<<"hider process command"<<endl;
  if(!currentState)
    std::cout<<"currentState null in hider::processCommand for player "<<player->getName()<<endl;
  std::cout<<currentState->printState();

  currentState->update(cmd, stateStack, player);

}

shared_ptr<RoleState> Hider::getInitialState(shared_ptr<Player> player)
{
  return make_shared<EnteredState>(player);
}
