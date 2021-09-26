#ifndef _SEQUENCESTATE_HPP
#define _SEQUENCESTATE_HPP
#include "RoleState.hpp"
#include "Point2d.hpp"

class SequenceState : public RoleState
{
public:

  SequenceState();
  typedef shared_ptr<vector<CommandType> > AllowedCmds;
  static AllowedCmds allowedCommands;


  static AllowedCmds initAllowedCmds()
  {
    AllowedCmds cmds = make_shared<vector<CommandType> >();
    cmds->push_back(CONTINUE);
    return cmds;
  }

  typedef map<AIPersonalityType, vector<int> > SequenceStatePersonalityCommandMap;
  static SequenceStatePersonalityCommandMap spcMap;

  static SequenceStatePersonalityCommandMap initSPCMap()
  {
    SequenceStatePersonalityCommandMap eMap;
    vector<int> vcare;
    vcare.push_back(1);
    vector<int> vfun;
    vfun.push_back(1);
    vector<int> vrisk;
    vrisk.push_back(1);
    vector<int> vnutty;
    vnutty.push_back(1);
    
    eMap[CAREFUL] = vcare;
    eMap[FUN] = vfun;
    eMap[RISKY] = vrisk;
    eMap[NUTTY] = vnutty;
    return eMap;
  }

private:
  
  int num;
  shared_ptr<SequenceState> next;
  shared_ptr<RoleState> endState;

public:
  void setOriginalCenter(shared_ptr<Point2d> center);
  shared_ptr<Point2d> getOriginalCenter();
  shared_ptr<SequenceState> getNextState();
  void setNextState(shared_ptr<SequenceState> next);
  void setSequence(int num);
  int getSequence();
  void setEndState(shared_ptr<RoleState> endState);
  shared_ptr<RoleState> getEndState();
  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player);
  virtual std::string printState() = 0;
  virtual void displayState(Engine *engine, shared_ptr<Player> player) = 0;
  
  virtual GameTimeType getGameTimeType();

protected:
  bool isDone;
  shared_ptr<Point2d> originalCenter;
  virtual shared_ptr<vector<CommandType> > getAllowedCommands();
  virtual shared_ptr<vector<int> > getWeights(AIPersonalityType personality);
  
};
#endif
