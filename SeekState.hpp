#ifndef _SEEKSTATE_H
#define _SEEKSTATE_H
#include "RoleState.hpp"
#include <vector>

class EnteredState;
class HiddenState;
class SeekState : public RoleState 
{
public:

  SeekState(shared_ptr<Player> player);
  ~SeekState();

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
    
    cmds->push_back(SEEK);
   

    
    cmds->push_back(MOVE);
    cmds->push_back(CHECK);
    
    
    return cmds;
  }

  

  typedef map<AIPersonalityType, vector<int> > SeekStatePersonalityCommandMap;
  static SeekStatePersonalityCommandMap spcMap;

  static SeekStatePersonalityCommandMap initSPCMap()
  {
    SeekStatePersonalityCommandMap eMap;
    vector<int> vcare;
    vcare.push_back(3);vcare.push_back(5);vcare.push_back(12);vcare.push_back(15); //These are cumulative sums
    vector<int> vfun;
    vfun.push_back(3);vfun.push_back(7);vfun.push_back(10);vfun.push_back(15);
    vector<int> vrisk;
    vrisk.push_back(5);vrisk.push_back(7);vrisk.push_back(10);vrisk.push_back(20);
    vector<int> vnuts;
    vnuts.push_back(5);vnuts.push_back(15);vnuts.push_back(16);vnuts.push_back(21);
    
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

  virtual void displayState(Engine *engine, shared_ptr<Player> player);

  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player);
  

protected:
  virtual shared_ptr<vector<CommandType> > getAllowedCommands();
  virtual shared_ptr<vector<int> > getWeights(AIPersonalityType personality);
  virtual void initAnimationSequence();

private:
  shared_ptr<Command> buildCommand(CommandType commandType);
  
  shared_ptr<AnimationSequence> initSeekAnimationSequence();
  
public:

private:
  bool isUP;
  shared_ptr<Player> player;
};
#endif
