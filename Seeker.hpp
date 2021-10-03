#ifndef _SEEKER_H
#define _SEEKER_H
#include "Role.hpp"
#include "SeekerWaitState.hpp"

class Seeker : public Role 
{
public:
  Seeker();

  _ROLECLONE(Seeker)

  virtual void processCommand(shared_ptr<Command> cmd, shared_ptr<Player> player);

  virtual shared_ptr<RoleState> getInitialState(shared_ptr<Player> player) override;
};
#endif
