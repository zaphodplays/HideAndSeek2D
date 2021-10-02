#ifndef _ROLESTATE_H
#define _ROLESTATE_H
#include <string>
#include <memory>
#include <stack>
#include "Command.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Enums.hpp"
#include "Engine.h"
#include "AnimationSequence.hpp"

using namespace std;

class Thing;
class Room;
class Player;

class RoleState : public enable_shared_from_this<RoleState> 
{
  
public:
  RoleState();

  shared_ptr<AnimationSequence> sequence;
  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player) = 0;
public:
  int getLocationID();
  void setLocationID(int id);
  virtual std::string printState() = 0;
  virtual void displayState(Engine *engine, shared_ptr<Player> player);
  virtual shared_ptr<vector<CommandType> > getAllowedCommands() = 0;
  virtual shared_ptr<vector<int> > getWeights(AIPersonalityType personality) = 0;
  virtual GameTimeType getGameTimeType();
public:
  shared_ptr<Command> getAICommand(AIPersonalityType personality);

  shared_ptr<Command> buildAICommand(CommandType commandType);
  
protected:
  virtual void initAnimationSequence();
  int locationid;
  GameTimeType gameTimeType;


};
#endif
