#include "Chair.hpp"


MAKE_PROTOTYPE(Chair)

Chair::Chair()
{
  this->thingtype = CHAIR;
  initAllowedRelations();
  center = make_shared<Point2d>();
}



void Chair::initAllowedRelations()
{
  shared_ptr<vector<RELATION> > hidevec = make_shared<vector<RELATION> >();
  hidevec->push_back(UNDER);
  hidevec->push_back(BEHIND);
  allowedRelMap[HIDE] = hidevec;

  shared_ptr<vector<RELATION> > jumpvec = make_shared<vector<RELATION> >();
  jumpvec->push_back(ON);
  allowedRelMap[JUMP] = jumpvec;
  
}

shared_ptr<vector<RELATION> > Chair::getAllowedRelationsForCmdType(CommandType commandType)
{
  return allowedRelMap.find(commandType)->second;
}


