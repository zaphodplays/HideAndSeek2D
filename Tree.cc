#include "Tree.hpp"


MAKE_PROTOTYPE(Tree)

Tree::Tree()
{
  this->thingtype = TREE;
  initAllowedRelations();
  center = make_shared<Point2d>();
}

void  Tree::initAllowedRelations()
{
  shared_ptr<vector<RELATION> > hidevec = make_shared<vector<RELATION> >();
  hidevec->push_back(ON);
  hidevec->push_back(BEHIND);
  
  
  allowedRelMap[HIDE] = hidevec;

}

shared_ptr<vector<RELATION> > Tree::getAllowedRelationsForCmdType(CommandType commandType)
{
  return allowedRelMap.find(commandType)->second;
}


