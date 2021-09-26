#include "Room.hpp"
#include "Thing.hpp"
#include "Player.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include "CommandParser.hpp"
#include "Enums.hpp"
#include "Chair.hpp"
#include "Tree.hpp"
#include "Seeker.hpp"
#include "Hider.hpp"

int main()
{
  shared_ptr<Room> hall = make_shared<Room>();
  hall->setID(1);
  hall->setRoomType(CENTRALHALL);

  
  shared_ptr<Room> pg = make_shared<Room>();
  pg->setID(2);
  pg->setRoomType(PLAYGROUND);
  

  shared_ptr<Thing> chair = make_shared<Chair>();
  shared_ptr<Thing> tree = make_shared<Tree>();
  shared_ptr<Thing> chair1 = make_shared<Chair>();
  shared_ptr<Thing> tree1 = make_shared<Tree>();


  shared_ptr<Thing> chair2 = Thing::makeThing("Chair");
  shared_ptr<Thing> tree2 = Thing::makeThing("Tree");
  shared_ptr<Thing> chair3 = Thing::makeThing("Chair");
  shared_ptr<Thing> tree3 = Thing::makeThing("Tree");
  shared_ptr<Thing> chair4 = Thing::makeThing("Chair");
  shared_ptr<Thing> tree4 = Thing::makeThing("Tree");

  hall->things->push_back(chair);
  hall->things->push_back(tree);

  pg->things->push_back(chair1);
  pg->things->push_back(tree1);

  
  shared_ptr<Room> bedroom = make_shared<Room>();
  bedroom->setID(3);
  bedroom->setRoomType(BEDROOM);
  bedroom->things->push_back(chair2);
  bedroom->things->push_back(tree2);

  shared_ptr<Room> livingroom = make_shared<Room>();
  livingroom->setID(4);
  livingroom->setRoomType(LIVINGROOM);
  livingroom->things->push_back(chair3);
  livingroom->things->push_back(tree3);

  shared_ptr<Room> diningroom = make_shared<Room>();
  diningroom->setID(5);
  diningroom->setRoomType(DININGROOM);
  diningroom->things->push_back(chair4);
  diningroom->things->push_back(tree4);

  Room::setRoomInDirection(NORTH, hall, pg);
  Room::setRoomInDirection(SOUTH, hall, bedroom);
  Room::setRoomInDirection(WEST, hall, livingroom);
  Room::setRoomInDirection(EAST, hall, diningroom);

  shared_ptr<Player> rayva = make_shared<UserPlayer>();
  rayva->centralhall = hall;
  rayva->setName("RayVa");

  shared_ptr<AIPlayer> clara = make_shared<AIPlayer>();
  clara->centralhall = hall;
  clara->setName("Clara");
  clara->personality = NUTTY;

  shared_ptr<AIPlayer> daniel = make_shared<AIPlayer>();
  daniel->centralhall = hall;
  daniel->setName("Daniel");
  daniel->personality = CAREFUL;

  rayva->role = make_shared<Hider>();
  rayva->initRoleState();
  clara->role = make_shared<Hider>();
  clara->initRoleState();
  daniel->role = make_shared<Hider>();
  daniel->initRoleState();

  shared_ptr<Command> cmdRayva = rayva->getCommand();
  shared_ptr<Command> cmdClara = clara->getCommand();
  shared_ptr<Command> cmdDaniel = daniel->getCommand();

  rayva->processCommand(cmdRayva);
  clara->processCommand(cmdClara);
  daniel->processCommand(cmdDaniel);

  cmdRayva = rayva->getCommand();
  cmdClara = clara->getCommand();
  cmdDaniel = daniel->getCommand();

  rayva->processCommand(cmdRayva);
  clara->processCommand(cmdClara);
  daniel->processCommand(cmdDaniel);

  while(true)
    {

      cmdRayva = rayva->getCommand();
      cmdClara = clara->getCommand();
      cmdDaniel = daniel->getCommand();

      rayva->processCommand(cmdRayva);
      clara->processCommand(cmdClara);
      daniel->processCommand(cmdDaniel);

    }

}
