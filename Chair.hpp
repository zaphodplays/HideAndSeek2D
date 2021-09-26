#include "Thing.hpp"
#include <vector>
#include <memory>
using namespace std;

class Chair : public Thing {
  
public :

  Chair();


  
  virtual shared_ptr<vector<RELATION> > getAllowedRelationsForCmdType(CommandType commandType);

  _CLONE(Chair)

protected:
  virtual void initAllowedRelations();



};
