#ifndef _PLAYER_H
#define _PLAYER_H
#include <memory>
#include <string>
#include "Engine.h"
#include "DisplayObject.hpp"
#include "Thing.hpp"
#include "Room.hpp"
#include "Command.hpp"
#include "Role.hpp"
#include "AnimationSequence.hpp"



class Room;
class Role;

class Player : public enable_shared_from_this<Player>
{
  
public:

  Player();

  static shared_ptr<Player> makePlayer(std::string type);
  static shared_ptr<Player>  addPlayer(std::string type, shared_ptr<Player> player);
  shared_ptr<Room> centralhall;
 
  
  void initRoleState();
  
  //needs a Role pointer
  shared_ptr<Role> role;
  
  
  //weak_ptr<Thing> thing;
  void setName(const std::string &name);
   const std::string &getName();

  std::string getFilename();
 void setFilename(std::string &name);
 
  Engine *getEngine();
  void setEngine(Engine *engine);
  void printState(int x, int y);
  virtual void displayState();
  void setColour(uint32_t dresscolour);
  //shared_ptr<DisplayObject> toggleDisplayObject();
  void shiftDisplay(int x, int y);
  shared_ptr<Point2d> getCenter();
  void setCenter(int x, int y);

  
  void setPlayerDisplay(PlayerDisplay pd);
  //void fixCenter();

  PlayerDisplay getPlayerDisplay();

  typedef map<std::string, shared_ptr<Player> > PlayerTypeTable;
  static PlayerTypeTable playerTypeTable;
  

  virtual shared_ptr<Command> getCommand() = 0;
  virtual shared_ptr<Player> clone() = 0;
  virtual void processCommand(shared_ptr<Command> cmd);
  virtual void initializePersonality(std::string type);


  virtual bool isAI() = 0;
 

protected:
  std::string name;
  
  
  uint32_t dresscolour;
  Engine *engine;
  shared_ptr<DisplayObject> displayObject;

  

private:
  //void initDisplayObject();
  //shared_ptr<DisplayObject> standingWithHandsUp;
  //shared_ptr<DisplayObject> standingWithHandsDown;
  //shared_ptr<DisplayObject> walkingPositionOne;
  //shared_ptr<DisplayObject> walkingPositionTwo;
  //shared_ptr<vector<shared_ptr<DisplayObject> > > standing;
  //void initStandingWithHandsUp();
  //void initStandingWithHandsDown();

public:
  typedef shared_ptr<map<std::string, shared_ptr<Player> > >  PlayerNameMap;
  static PlayerNameMap playerNameMap;

  static PlayerNameMap initPlayerNameMap()
  {
    PlayerNameMap pmap = make_shared<map<std::string, shared_ptr<Player> > >();
    return pmap;
  }

  static PlayerTypeTable initPlayerTypeTable() {
      PlayerTypeTable pTable;
      return pTable;
    }
public:


private:
  shared_ptr<Point2d> center;
 
 
  std::string filename;
  PlayerDisplay playerDisplay;
  int framenum;
 
};

#define _PLAYERCLONE(TYPE) \
  virtual shared_ptr<Player> clone()  { return  make_shared<TYPE>(); }

#define MAKE_PLAYERTYPE(TYPE) \
  shared_ptr<Player> TYPE ## _p(new TYPE());	\
   shared_ptr<Player> TYPE ## _myProtoype = \
     Player::addPlayer(#TYPE, TYPE ## _p);


#endif
