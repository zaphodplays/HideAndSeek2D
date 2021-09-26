#ifndef _ROLE_H
#define _ROLE_H
#include <string>
#include <memory>
#include <stack>
#include "Command.hpp"
#include "Thing.hpp"
#include "RoleState.hpp"
#include "Enums.hpp"

using namespace std;


class RoleState;

class Role {
  
public:

  virtual shared_ptr<Role> clone() = 0;

  static shared_ptr<Role> makeRole(std::string type);
  static shared_ptr<Role>  addRole(std::string type, shared_ptr<Role> role);

  shared_ptr<stack< shared_ptr<RoleState> > > stateStack;

  virtual void processCommand(shared_ptr<Command> cmd, shared_ptr<Player> player) = 0;

  void initStateStack(shared_ptr<RoleState> initialState);

  typedef map<std::string, shared_ptr<Role> > RoleTable;
  static RoleTable roleTable;

   static RoleTable initRoleTable() {
      RoleTable rTable;
      return rTable;
    }
  
};

#define _ROLECLONE(TYPE) \
  virtual shared_ptr<Role> clone()  { return  make_shared<TYPE>(); }

#define MAKE_ROLETYPE(TYPE) \
  shared_ptr<Role> TYPE ## _p(new TYPE());	\
   shared_ptr<Role> TYPE ## _myProtoype = \
     Role::addRole(#TYPE, TYPE ## _p);

#endif
