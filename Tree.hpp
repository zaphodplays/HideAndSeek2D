#include "Thing.hpp"
using namespace std;

class Tree: public Thing {

public:
  Tree();
  virtual shared_ptr<vector<RELATION> > getAllowedRelationsForCmdType(CommandType commandType);

  
  _CLONE(Tree)
  
protected:
  virtual void initAllowedRelations();
  


};
