#include "Role.hpp"

Role::RoleTable Role::roleTable = initRoleTable();

shared_ptr<Role> Role::makeRole(std::string type)
{
  
  shared_ptr<Role> proto = roleTable.find(type)->second;
  if( proto == nullptr )
    return proto;
  return proto->clone();
}

shared_ptr<Role> Role::addRole(std::string type, shared_ptr<Role> p)
{
  //std::cout<<"adding prototype  for thing type "<<type<<endl;
  
  roleTable[type] = p;
  //std::cout<<"done"<<endl;
  return p;
}


void Role::initStateStack(shared_ptr<RoleState> initialState)
{
  stateStack->push(initialState);
}
