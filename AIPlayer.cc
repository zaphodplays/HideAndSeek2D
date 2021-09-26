#include "AIPlayer.hpp"

MAKE_PLAYERTYPE(AIPlayer)

AIPlayer::PersonalityMap AIPlayer::pmap = AIPlayer::initPMap();

AIPlayer::AIPlayer()
{
  
}

shared_ptr<Command> AIPlayer::getCommand()
{
  shared_ptr<RoleState> currentState = role->stateStack->top();
  //std::cout<<"player : "<<getName()<<endl;
  return currentState->getAICommand(personality);
}



void AIPlayer::initializePersonality(std::string type)
{
  this->personality = AIPlayer::getPersonalityType(type);
}

bool AIPlayer::isAI() 
{
  return true;
}

