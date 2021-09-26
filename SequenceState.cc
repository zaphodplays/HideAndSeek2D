#include "SequenceState.hpp"

SequenceState::AllowedCmds SequenceState::allowedCommands = initAllowedCmds();
SequenceState::SequenceStatePersonalityCommandMap SequenceState::spcMap = initSPCMap();

SequenceState::SequenceState()
{
  gameTimeType = FASTTIME;
}

GameTimeType SequenceState::getGameTimeType()
{
  return gameTimeType;
}

shared_ptr<vector<int> > SequenceState::getWeights(AIPersonalityType personality)
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = spcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > SequenceState::getAllowedCommands()
{
  return SequenceState::allowedCommands;
}

void SequenceState::setOriginalCenter(shared_ptr<Point2d> center)
{
  originalCenter = center;
}

shared_ptr<Point2d> SequenceState::getOriginalCenter()
{
  return originalCenter;
}


void SequenceState::setNextState(shared_ptr<SequenceState> next)
{
  this->next = next;
}

shared_ptr<SequenceState> SequenceState::getNextState()
{
  return next;
}

void SequenceState::setSequence(int num)
{
  this->num = num;
}

int SequenceState::getSequence()
{
  return num;
}

shared_ptr<RoleState> SequenceState::getEndState()
{
  return endState;
}

void SequenceState::setEndState(shared_ptr<RoleState> endState)
{
  this->endState = endState;
}

void SequenceState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
  std::cout<<"sequencestate::update"<<endl;  
  if(!isDone)
    {
      std::cout<<"sequencestate::is done is false, returning"<<endl;
      return;
    }
  if(isDone && !next && endState)
    {
      int numStatesToPop = getSequence();
      endState->setLocationID(getLocationID());
      
      for(int i = 1; i <= numStatesToPop; i++)
	{
	  stateStack->pop();
	}
      
      stateStack->push(endState);
      
    }
  else
    {
      stateStack->push(next);
    }
  std::cout<<"sequencestate::update end"<<endl;
}
