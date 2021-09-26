#ifndef _ENTEREDSTATE_H
#define _ENTEREDSTATE_H
#include "RoleState.hpp"
#include "HiddenState.hpp"
#include "JumpingState.hpp"
#include <vector>

class HiddenState;
class JumpingState;

class EnteredState : public RoleState 
{
public:
  
  EnteredState(shared_ptr<Player> player);
  
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
    cmds->push_back(LIGHTS);
    cmds->push_back(HIDE);
    cmds->push_back(MOVE);
    cmds->push_back(JUMP);
    return cmds;
  }

  

  typedef map<AIPersonalityType, vector<int> > EnteredStatePersonalityCommandMap;
  static EnteredStatePersonalityCommandMap epcMap;

  static EnteredStatePersonalityCommandMap initEPCMap()
  {
    EnteredStatePersonalityCommandMap eMap;
    vector<int> vcare;
    vcare.push_back(3);vcare.push_back(5);vcare.push_back(12);vcare.push_back(15);vcare.push_back(16); //These are cumulative sums
    vector<int> vfun;
    vfun.push_back(3);vfun.push_back(7);vfun.push_back(10);vfun.push_back(15);vfun.push_back(20);
    vector<int> vrisk;
    vrisk.push_back(5);vrisk.push_back(7);vrisk.push_back(10);vrisk.push_back(20);vrisk.push_back(27);
    vector<int> vnuts;
    vnuts.push_back(5);vnuts.push_back(15);vnuts.push_back(16);vnuts.push_back(21);vnuts.push_back(31);
    
    eMap[CAREFUL] = vcare;
    eMap[FUN] = vfun;
    eMap[RISKY] = vrisk;
    eMap[NUTTY] = vnuts;
    return eMap;
  }

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


  virtual std::string printState();

  
  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player);
  

protected:
  virtual void initAnimationSequence();
  virtual shared_ptr<vector<CommandType> > getAllowedCommands();
  virtual shared_ptr<vector<int> > getWeights(AIPersonalityType personality);

private:
  shared_ptr<Command> buildCommand(CommandType commandType);
  shared_ptr<AnimationSequence> initStandingAnimationSequence();
  shared_ptr<Player> player;
};
#endif
