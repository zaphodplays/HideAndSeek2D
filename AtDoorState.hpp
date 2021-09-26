#ifndef _ATDOORSTATE_HPP
#define _ATDOORSTATE_HPP
#include "SequenceState.hpp"

class AtDoorState : public SequenceState
{
public:

  AtDoorState();
  void initState(shared_ptr<Point2d> originalCenter, int roomid, Direction direction, bool toPass);
  
  
  shared_ptr<RoleState> getRoleState();

  virtual std::string printState();

  virtual void displayState(Engine *engine, shared_ptr<Player> player);

  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player);

protected:

  void initAnimationSequence();


  //virtual void displayState(Engine *engine, shared_ptr<Player> player);

  
private:
  bool toPass;
  shared_ptr<Point2d> doorcenter;
  Direction direction;
  void setDirection(Direction direction);
  void passThrough(shared_ptr<Player> player);
  shared_ptr<AnimationSequence> initStandingAnimationSequence();

};
#endif
