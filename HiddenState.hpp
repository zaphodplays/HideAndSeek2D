#ifndef _HIDDENSTATE_H
#define _HIDDENSTATE_H
#include "RoleState.hpp"
#include "PeekState.hpp"
#include "EnteredState.hpp"
#include <memory>

class PeekState;
class EnteredState;
class HiddenState : public RoleState 
{
public:

  HiddenState();

  typedef shared_ptr<vector<CommandType> > AllowedCmds;
  static AllowedCmds allowedCommands;
  /**                                                                                                                                                                                
  LIST,                                                                                                                                                                              
    LOOK,                                                                                                                                                                            
    LIGHTS,                                                                                                                                                                          
    HIDE,                                                                                                                                                                            
    UNHIDE,                                                                                                                                                                          
    PEEK,                                                                                                                                                                            
    RUN,                                                                                                                                                                             
    CHECK,                                                                                                                                                                           
    MOVE,                                                                                                                                                                            
  **/


  static AllowedCmds initAllowedCmds()
  {
    AllowedCmds cmds = make_shared<vector<CommandType> >();
    cmds->push_back(LOOK);
    cmds->push_back(UNHIDE);
    cmds->push_back(PEEK);
    
    return cmds;
  }



  typedef map<AIPersonalityType, vector<int> > HiddenStatePersonalityCommandMap;
  static HiddenStatePersonalityCommandMap hpcMap;

  static HiddenStatePersonalityCommandMap initHPCMap()
  {
    HiddenStatePersonalityCommandMap eMap;
    vector<int> vcare;
    vcare.push_back(6);vcare.push_back(9);vcare.push_back(12); 
    vector<int> vfun;    
    vfun.push_back(3);vfun.push_back(10);vfun.push_back(20);
    vector<int> vrisk;
    vrisk.push_back(1);vrisk.push_back(11);vrisk.push_back(13);
    vector<int> vnutty;
    vnutty.push_back(5);vnutty.push_back(10);vnutty.push_back(15);
    eMap[CAREFUL] = vcare;
    eMap[FUN] = vfun;
    eMap[RISKY] = vrisk;
    eMap[NUTTY] = vnutty;
    return eMap;
  }

public:

  virtual std::string printState();

  virtual void displayState(Engine *engine, shared_ptr<Player> player);

  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr< RoleState > > > stateStack, shared_ptr<Player> player);

protected:

  virtual shared_ptr<vector<CommandType> > getAllowedCommands();

  virtual shared_ptr<vector<int> > getWeights(AIPersonalityType personality);

  virtual void initAnimationSequence();

};
#endif
