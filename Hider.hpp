#ifndef _HIDER_H
#define _HIDER_H
#include "Role.hpp"

class Hider : public Role {


public:

  Hider();

  _ROLECLONE(Hider)

  void processCommand(shared_ptr<Command> cmd, shared_ptr<Player> player);

};
#endif
