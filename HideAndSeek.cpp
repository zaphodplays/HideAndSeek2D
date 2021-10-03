#include "Engine.h"
#include "time.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <memory>
#include "Room.hpp"
#include "Thing.hpp"
#include "Player.hpp"
#include "FoundState.hpp"
#include "UserPlayer.hpp"
#include "AIPlayer.hpp"
#include "CommandParser.hpp"
#include "Enums.hpp"
#include "Chair.hpp"
#include "Tree.hpp"
#include "Door.hpp"
#include "Seeker.hpp"
#include "Hider.hpp"
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

using namespace std;



shared_ptr<Thing> createThing(json &jthing);
shared_ptr<Room> createRoom(json &jroom);
shared_ptr<Player> createPlayer(json &jplayer);
void connectRooms(json &jmap);
void setupPlayer(Player &player, Engine *engine, shared_ptr<Room> hall);

void createWorld(shared_ptr<UserPlayer> &auser, list<shared_ptr<AIPlayer> > &aiplayers)
{
	// read a JSON file
	ifstream i("data.json");
	json j;
	//i>>j;
	std::cout<<"before parse" << endl;
	j = json::parse(i);
	//std::cout<<j["hideseekworld"]["rooms"]<<endl;
	//json::array(j["hideseekworld"]["things"]);
	json::iterator jitor = (j["hideseekworld"]["rooms"]).begin();
	while(jitor != (j["hideseekworld"]["rooms"]).end())
	{
		json jroom = *jitor;
		std::cout<<"room id = " << jroom["id"] << endl;
		shared_ptr<Room> room = createRoom(jroom);
		jitor++;
	}
	connectRooms(j["hideseekworld"]["worldmap"]);
	
	json::iterator jplaytor = j["hideseekworld"]["player"].begin();
	while(jplaytor != (j["hideseekworld"]["player"]).end() )
	{
		json jplayer = *jplaytor;
		std::cout<<"player name = "<<jplayer["name"]<<endl;
		shared_ptr<Player> player = createPlayer(jplayer);
		
		if(player->isAI())
		{
			
			shared_ptr<AIPlayer> aiplayer(dynamic_pointer_cast<AIPlayer>(player) );
			aiplayers.push_back(aiplayer);
		}
		else
		{
			shared_ptr<UserPlayer> user(dynamic_pointer_cast<UserPlayer>(player) );
			auser = user;
		}
			
		jplaytor++;
	}
	

}

shared_ptr<Player> createPlayer(json &jplayer)
{

	shared_ptr<Player> player = Player::makePlayer(jplayer["type"]);
	std::string filename = jplayer["file"];
	player->setFilename(filename);
	player->setCenter( jplayer["x"].get<int>(), jplayer["y"].get<int>() );
	shared_ptr<Room> hall = Room::roomIDMap->find(1)->second;
	player->centralhall = hall;
	std::string rolename = jplayer["role"];
	player->role = Role::makeRole(rolename);
	player->initRoleState();
	
	std::string name = jplayer["name"];
	player->setName(name);
	
	
	
	std::string personality;
	personality = jplayer["personality"];
	
	player->initializePersonality(personality);
	return player;
	
}

void connectRooms(json &jmap)
{
	json::iterator jwmaptor = jmap.begin();
	while(jwmaptor != jmap.end())
	{
		json jelem = *jwmaptor;
		std::cout<<" map id = "<<jelem["id"]<<endl;
		std::cout<<"map = "<<jelem<<endl;
		std::cout<<"n = "<<jelem["n"]<<endl;
		int id = jelem["id"].get<int>();
		std::cout<<"id = "<<id<<endl;
		shared_ptr<Room> thisroom = Room::roomIDMap->find(id)->second;
		if(!thisroom)
			std::cout<<"this room is null"<<endl;
		std::cout<<"we are here"<<endl;
		
		std::cout<<"we are there"<<endl;
		if(jelem.contains("n"))
		{
			std::cout<<"n = "<<jelem["n"]<<endl;
			int north_room_id = jelem["n"].get<int>();
			shared_ptr<Room> north_room = Room::roomIDMap->find(north_room_id)->second;	
			Room::connect(NORTH, thisroom, north_room);
		}
		if(jelem.contains("s"))
		{
			int south_room_id = jelem["s"].get<int>();
			shared_ptr<Room> south_room = Room::roomIDMap->find(south_room_id)->second;	
			Room::connect(SOUTH, thisroom, south_room);
		}
		if(jelem.contains("w"))
		{
			int west_room_id = jelem["w"].get<int>();
			shared_ptr<Room> west_room = Room::roomIDMap->find(west_room_id)->second;	
			Room::connect(WEST, thisroom, west_room);
		}
		if(jelem.contains("e"))
		{
			int east_room_id = jelem["e"].get<int>();
			shared_ptr<Room> east_room = Room::roomIDMap->find(east_room_id)->second;	
			Room::connect(EAST, thisroom, east_room);
		}
		jwmaptor++;
	}
}

shared_ptr<Thing> createThing(json &jthing)
{
	shared_ptr<Thing> thing = Thing::makeThing(jthing["name"]);
	thing->setFilename(jthing["file"]);
	thing->setName(jthing["name"]);
	thing->setCenter( jthing["x"].get<int>(), jthing["y"].get<int>() );
	return thing;
}

shared_ptr<Room> createRoom(json &jroom)
{
	std::cout<<"room name = "<<jroom["name"]<<endl;
	std::string name = jroom["name"];
	std::string filename = jroom["file"];
	shared_ptr<Room> aroom = make_shared<Room>(name, filename, 0, 0);
	aroom->setID(jroom["id"]);
	
	std::cout<<"name = "<<aroom->getName()<<endl;
	
	//std::cout<<"things = "<<jroom["thing"]<<endl;
	json::iterator jthingitor = jroom["thing"].begin();

	while(jthingitor != jroom["thing"].end())
	{
		json jthing = *jthingitor;
		std::cout<<"thing = " << jthing <<endl;
		shared_ptr<Thing> thing = createThing(jthing);
		aroom->things->push_back(thing);	
		jthingitor++;
	}
	
	
	return aroom;
	
}

void setupPlayer(shared_ptr<Player> player, Engine *engine, shared_ptr<Room> room)
{
	if(player == nullptr)
		{
			cout<<"player is null"<<endl;
			return;
		}
	player->setEngine(engine);
	player->centralhall = room;
	
	if(!player->isAI())
		room->setUserPlayerPresent();
	room->addPlayer(player->getName());	
}

void EngineMain()
{
	//srand((int) time(0));
	std::cout<<"before creating world"<<endl;
	Engine* engine = new Engine();
	if(engine == nullptr)
		cout<<"engine is null"<<endl;
	std::string hellotext = "engine is alive";
	engine->drawText(hellotext.c_str(), 200, 550);
	list<shared_ptr<Player> > players;
	list<shared_ptr<AIPlayer> > aiplayers;
	shared_ptr<UserPlayer> user;
	
	createWorld(user, aiplayers);
	std::cout<<"finished creating world"<<endl;
	map<int, shared_ptr<Room> >::iterator roomitor = Room::roomIDMap->begin();
	vector<shared_ptr<Room> > rooms;
	for(; roomitor != Room::roomIDMap->end(); roomitor++)
	{
		int id = roomitor->first;
		shared_ptr<Room> room = roomitor->second;
		rooms.push_back(room);
		std::cout<<"room id = "<<id<<endl;
		
	}
	
	shared_ptr<Room> hall = Room::roomIDMap->find(1)->second;
	hall->setUserPlayerPresent();
	std::cout<<"FINISHED CONNECTING ROOMS"<<endl;
	engine->drawText(hellotext.c_str(), 200, 650);
	shared_ptr<Player> player = shared_ptr<Player>(user);
	if(player == nullptr)
		{
			cout<<"casted player is null"<<endl;
			return;
		}
	setupPlayer(player, engine, hall);
	list<shared_ptr<AIPlayer> >::iterator pitor = aiplayers.begin();
	while(pitor != aiplayers.end())
	{
		shared_ptr<AIPlayer> aiplayer = *pitor;
		shared_ptr<Player> aplayer = static_pointer_cast<Player>(aiplayer);
		int random_room_idx = rand()%rooms.size();
		
		setupPlayer(aplayer, engine, rooms[random_room_idx]);
		pitor++;
	}
	engine->drawText(hellotext.c_str(), 200, 700);
	
	shared_ptr<Command> cmdUser;


	std::cout<<"before starting game "<<user->role->stateStack->top()->printState()<<endl;


	
	double atime = 0;
	double rtime = 0;
	double ftime = 0;
	double btime = 0;
	double utime = 0;
	double seqtime = 0;
	const double SEQSECS = 0.1;
	const double CMDSECS = 1;
	const double FPS = 0.1;
	
	
	while (engine->startFrame())
	{
		double timestamp = engine->getStopwatchElapsedSeconds();
		
		
		//Engine::PlayerInput keys;
		std::string input;
		//std::cout<<"HELLLOO"<<endl;
		//cmdRayva = rayva->getCommand();
	        //cmdClara = clara->getCommand();
		

		//engine.drawSprite(Engine::NewSprite, 644, 420);
		std::cout<<"just before getting cmd input"<<endl;
		cmdUser = user->getCommand();
		std::cout<<"just after cmd input, cmd type is "<<cmdUser->commandType<<endl;
		user->processCommand(cmdUser);
		std::cout<<"after process cmd"<<endl;
		if(timestamp - utime > SEQSECS)
		  {
			list<shared_ptr<AIPlayer> >::iterator pitor = aiplayers.begin();
			while(pitor != aiplayers.end())
			{
				shared_ptr<AIPlayer> aiplayer = *pitor;
				shared_ptr<Command> cmdPlayer;
				if(aiplayer->role->stateStack->top()->getGameTimeType() == FASTTIME)
				{
					cmdPlayer = aiplayer->getCommand();
					aiplayer->processCommand(cmdPlayer);
				}
				pitor++;	
			}
		    
		    utime = timestamp;
			
		  }
		if(timestamp - btime > CMDSECS)
		{

		  	list<shared_ptr<AIPlayer> >::iterator pitor = aiplayers.begin();
			while(pitor != aiplayers.end())
			{
				
				shared_ptr<Player> aiplayer = *pitor;
				if(aiplayer->isAI())
				{
					shared_ptr<Command> cmdPlayer;
					if(aiplayer->role->stateStack->top()->getGameTimeType() == NORMALTIME)
					{
						cmdPlayer = aiplayer->getCommand();
						aiplayer->processCommand(cmdPlayer);
					}
				}
				
				pitor++;	
			}

		  
			
		     btime = timestamp;
		     
		}
		if(timestamp - ftime < 0.001)
			continue;
		std::cout<<"just before print state invoc"<<endl;
		user->printState(200,510);
		std::cout<<"just before displaying location id"<<endl;
		std::cout<<user->role->stateStack->top()->getLocationID()<<endl;
		
		Room::roomIDMap->find(user->role->stateStack->top()->getLocationID())->second->display(engine);
		ftime = timestamp;
		int x = 200, y = 540;
		pitor = aiplayers.begin();
		while(pitor != aiplayers.end())
		{
			
			shared_ptr<Player> aiplayer = *pitor;
			shared_ptr<RoleState> state = aiplayer->role->stateStack->top();
			shared_ptr<FoundState> foundState(dynamic_pointer_cast<FoundState>(state) );
			if(foundState != nullptr)
				aiplayer->printState(x,y);
			y = y + 30;
			pitor++;	
		}
		
		
		
		  
		
	}
	delete engine;
	engine = 0;
	
}

void executeCommandOnTime(double timestamp, double utime, shared_ptr<Player> player)
{
  
}


