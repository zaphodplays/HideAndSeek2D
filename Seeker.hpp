#ifndef _SEEKER_H
#define _SEEKER_H
#include "Role.hpp"

class Seeker : public Role 
{
public:
  Seeker();

  _ROLECLONE(Seeker)

  virtual void processCommand(shared_ptr<Command> cmd, shared_ptr<Player> player);
};
#endif
