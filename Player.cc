#include "Player.hpp"
#include "Line.hpp"
#include "Polygon.hpp"
#include "Circle.hpp"
#include "Room.hpp"
#include "EnteredState.hpp"

Player::PlayerNameMap Player::playerNameMap = Player::initPlayerNameMap();
Player::PlayerTypeTable Player::playerTypeTable = initPlayerTypeTable();



Player::Player()
{
  //standing = make_shared<vector<shared_ptr<DisplayObject> > >();
  //initDisplayObject();
  displayObject = make_shared<DisplayObject>();
  std::cout<<"in player constructor"<<endl;
  center = make_shared<Point2d>();
  
}
/*
void Player::initDisplayObject()
{
  initStandingWithHandsUp();
  initStandingWithHandsDown();
}
*/
void Player::setPlayerDisplay(PlayerDisplay pd)
{
  playerDisplay = pd;
}

PlayerDisplay Player::getPlayerDisplay()
{
  return playerDisplay;
}

const std::string &Player::getName()
{
  return name;
}

void Player::setFilename(std::string &name)
{
  this->filename = name;
  displayObject->setFilename(name);
}

std::string Player::getFilename()
{
  return filename;
}



shared_ptr<Player> Player::makePlayer(std::string type)
{
  
  shared_ptr<Player> proto = playerTypeTable.find(type)->second;
  if( proto == nullptr )
    return proto;
  return proto->clone();
}

shared_ptr<Player> Player::addPlayer(std::string type, shared_ptr<Player> p)
{
  //std::cout<<"adding prototype  for thing type "<<type<<endl;
  
  playerTypeTable[type] = p;
  //std::cout<<"done"<<endl;
  return p;
}

/**
shared_ptr<DisplayObject> Player::toggleDisplayObject()
{
  std::cout<<"in toggledisplay"<<endl;
  shared_ptr<AnimationSequence> seq = playerDisplayMap->find(playerDisplay)->second;
  int size = seq->getSize();
  int x = rand() % size;
  std::cout<<"toggle x = "<<x<<endl;
  return seq->getDisplayObject(x);
  
}**/

shared_ptr<Point2d> Player::getCenter()
{
  //shared_ptr<DisplayObject> dp = toggleDisplayObject();
  return center;
}

void Player::setCenter(int x, int y)
{
  center->set(x, y);
}

/*
void Player::fixCenter()
{
  std::cout<<"fixCenter()::begin"<<endl;
  if(this->role->stateStack->top()->sequence)
    std::cout<<"fixCenter()::sequence center is "<<this->role->stateStack->top()->sequence->getCenter()->x<<endl;;
  int x = ((this->role->stateStack->top()->sequence))->getCenter()->x;
  int y = ((this->role->stateStack->top()->sequence))->getCenter()->y;
  this->center->set(x,y);
  std::cout<<"fixCenter::end"<<endl;
}
*/

void Player::setName(const std::string &name)
{
  this->name = name;
  this->role->stateStack->top()->sequence->setName(name);
  /*map<PlayerDisplay, shared_ptr<AnimationSequence> >::iterator it;

    for ( it = playerDisplayMap->begin(); it != playerDisplayMap->end(); it++ )
      {
	    //std::cout << it->first  // std::string (key)
	    //	  << ':'
	    //	  << it->second   // std::string's value 
	    //	  << std::endl ;
	      it->second->setName(name);
      }
  
  //(*standing)[0]->setText(name, 371, 312);
  //(*standing)[1]->setText(name, 371, 312);*/
  (*playerNameMap)[name] = shared_from_this();
}

void Player::shiftDisplay(int x, int y)
{
  std::cout<<"Player::shiftDisplay"<<endl;
  //(*standing)[0]->shift(x,y);
  //(*standing)[1]->shift(x,y);
  center->x += x;
  center->y += y;
  //map<PlayerDisplay, shared_ptr<AnimationSequence> >::iterator it;

  /*for ( it = playerDisplayMap->begin(); it != playerDisplayMap->end(); it++ )
    {
    //std::cout << it->first  // std::string (key)
    //	  << ':'
    //	  << it->second   // std::string's value 
    //	  << std::endl ;
      it->second->shiftDisplays(x, y);*/
    //}
  
  ((this->role->stateStack->top()->sequence))->shiftDisplays(x, y);
  //std::cout<<"Player::shiftDisplays end"<<endl;
}



void Player::setColour(uint32_t dresscolour)
{
  this->dresscolour = dresscolour;
  this->role->stateStack->top()->sequence->setColour(dresscolour);
  //(*(displayObject->getCircles() ))[0]->circumcolour = dresscolour;
  //(*((*standing)[0])->getPolygons())[0]->incolour = dresscolour;
  //(*((*standing)[1])->getPolygons())[0]->incolour = dresscolour;
  //map<PlayerDisplay, shared_ptr<AnimationSequence> >::iterator it;
/*
  for ( it = playerDisplayMap->begin(); it != playerDisplayMap->end(); it++ )
    {
    //std::cout << it->first  // std::string (key)
    //	  << ':'
    //	  << it->second   // std::string's value 
    //	  << std::endl ;
      if(it->first == STANDING || it->first == JUMPING )
        it->second->setColour(dresscolour);
    }
    */
}

Engine* Player::getEngine()
{
  return engine;
}

void Player::setEngine(Engine *engine)
{
  this->engine = engine;
}

void Player::printState(int x, int y)
{
  //std::cout<<"Player::printState()";
  std::string print = name + ":: " + role->stateStack->top()->printState();
  //std::cout<<"still Player::printState() "<<print<<" "<<endl;
  print += "x = " + to_string(getCenter()->x) + " y = " + to_string(getCenter()->y);
  engine->drawText(print.c_str(), x, y);
}

void Player::displayState()
{
  
  //std::cout<<"going to display state as room"<<this->role->stateStack->top()->location->getRoomType()<<endl;
  
  
  //shared_ptr<DisplayObject> dp = toggleDisplayObject();
  //std::cout<<"toggledDisplayObject"<<endl;
  //int x = rand() % 10;
  
  //int r = rand() % 2;
  //      r == 0 ? shiftDisplay(x,0) : shiftDisplay(-1*x, 0);
  
  //shiftDisplay(5,0);
  //this->role->stateStack->top()->displayState(engine);
  //dp->display(engine);
  //std::cout<<"displayed Object"<<endl;
  
}
void Player::processCommand(shared_ptr<Command> cmd)
{
  //std::cout<<"processing player "<<getName()<<endl;
  this->role->processCommand(cmd, shared_from_this());
}

void Player::initRoleState()
{
  
  shared_ptr<RoleState> state = role->getInitialState(shared_from_this());
  state->setLocationID(this->centralhall->getID());
  role->initStateStack(state);
}
  
void Player::initializePersonality(std::string type)
{
  //do nothing really
}


