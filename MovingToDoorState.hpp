#ifndef _MOVINGTODOORSTATE_HPP
#define _MOVINGTODOORSTATE_HPP

class MovingToDoorState : public RoleState
{
public:

  typedef shared_ptr<vector<CommandType> > AllowedCmds;
  static AllowedCmds allowedCommands;

  shared_ptr<vector<shared_ptr<Point2d> > > linepoints;
  
  static AllowedCmds initAllowedCmds()
  {
    AllowedCmds cmds = make_shared<vector<CommandType> >();
    return cmds;
  }

  shared_ptr<RoleState> getRoleState();

  virtual void printState();

  virtual void update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player);

protected:
  virtual shared_ptr<vector<CommandType> > getAllowedCommands();
  virtual shared_ptr<vector<int> > getWeights(AIPersonalityType personality);

private:
  shared_ptr<Command> buildCommand(CommandType commandType);
  shared_ptr<Door> door;
  int currentRoomID;
  int nextRoomID;
  Point2d doorcenter;
  Point2d originalPosition;
  Direction dir;

  void setDirection(Direction direction);
  void calculate collinearPoints(shared_ptr<Point2d> point1, shared_ptr<Point2d> point2);
  

  

};
#endif
