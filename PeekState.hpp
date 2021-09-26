#ifndef _PEEKSTATE_H
#define _PEEKSTATE_H
#include "RoleState.hpp"


class PeekState : public RoleState 
{
public:

  PeekState();
  
  typedef shared_ptr<vector<CommandType> > AllowedCmds;
  static AllowedCmds allowedCommands;
  /**                                                                                                                                                                               \
                                                                                                                                                                                     
  LIST,                                                                                                                                                                             \
                                                                                                                                                                                     
    LOOK,                                                                                                                                                                           \
                                                                                                                                                                                     
    LIGHTS,                                                                                                                                                                         \
                                                                                                                                                                                     
    HIDE,                                                                                                                                                                           \
                                                                                                                                                                                     
    UNHIDE,                                                                                                                                                                         \
                                                                                                                                                                                     
    PEEK,                                                                                                                                                                           \
                                                                                                                                                                                     
    RUN,                                                                                                                                                                            \
                                                                                                                                                                                     
    CHECK,                                                                                                                                                                          \
                                                                                                                                                                                     
    MOVE,                                                                                                                                                                           \
                                                                                                                                                                                     
  **/


  static AllowedCmds initAllowedCmds()
  {
    AllowedCmds cmds = make_shared<vector<CommandType> >();
    cmds->push_back(LOOK);
    cmds->push_back(UNHIDE);
    cmds->push_back(HIDE);

    return cmds;
  }

  typedef map<AIPersonalityType, vector<int> > PeekStatePersonalityCommandMap;
  static PeekStatePersonalityCommandMap ppcMap;

  static PeekStatePersonalityCommandMap initPPCMap()
  {
    PeekStatePersonalityCommandMap eMap;
    vector<int> vcare;
    vcare.push_back(6);vcare.push_back(9);vcare.push_back(19);
    vector<int> vfun;
    vfun.push_back(5);vfun.push_back(10);vfun.push_back(15);
    vector<int> vrisk;
    vrisk.push_back(10);vrisk.push_back(20);vrisk.push_back(22);
    vector<int> vnutty;
    vnutty.push_back(10);vnutty.push_back(30);vnutty.push_back(35);
    
    eMap[CAREFUL] = vcare;
    eMap[FUN] = vfun;
    eMap[RISKY] = vrisk;
    eMap[NUTTY] = vnutty;
    return eMap;
  }

public:

  virtual std::string printState();

  virtual void displayState(Engine *engine, shared_ptr<Player> player);
  
  virtual void update(shared_ptr<Command> cmd, shared_ptr< stack<shared_ptr< RoleState> > > stateStack, shared_ptr<Player> player);

protected:

  virtual shared_ptr<vector<CommandType> > getAllowedCommands();
  
  virtual shared_ptr<vector<int > > getWeights(AIPersonalityType personality);

  virtual void initAnimationSequence();

private:

  shared_ptr<AnimationSequence> initPeekAnimationSequence();

};
#endif
