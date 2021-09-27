#ifndef _MOVINGSTATE_HPP
#define _MOVINGSTATE_HPP
#include "SequenceState.hpp"


class MovingState : public SequenceState
{
public:
  MovingState(shared_ptr<Player> player);
  void initState(int roomid, shared_ptr<Point2d> targetCenter, shared_ptr<Point2d> originalCenter);
  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player);
  virtual std::string printState();
  virtual void displayState(Engine *engine, shared_ptr<Player> player);
  
private:
  
  shared_ptr<vector<shared_ptr<Point2d> > > linepoints;

public:
  
  shared_ptr<RoleState> getRoleState();

    

  
private:
  
  shared_ptr<Point2d> targetCenter;
  shared_ptr<Player> player;

  
  
  void calculateCollinearPoints();
  
  shared_ptr<vector<shared_ptr<Point2d> > > getCollinearPointsBetween(shared_ptr<Point2d> point1, shared_ptr<Point2d> point2);

  bool hasReached(shared_ptr<Player> player);
  void keepMoving(shared_ptr<Player> player);

  shared_ptr<AnimationSequence> initMoveAnimationSequence();

protected:

  virtual void initAnimationSequence();
  
};
#endif
