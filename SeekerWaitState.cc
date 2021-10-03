#include "SeekerWaitState.hpp"
#include "SeekState.hpp"
#include "EnteredState.hpp"
#include "HiddenState.hpp"
#include <iostream>
using namespace std;


SeekerWaitState::AllowedCmds SeekerWaitState::allowedCommands = initAllowedCmds();;
SeekerWaitState::SeekerWaitStatePersonalityCommandMap SeekerWaitState::jpcMap = initJPCMap();
const int SeekerWaitState::WAITSECONDS = 30;

SeekerWaitState::SeekerWaitState(shared_ptr<Player> player, Engine *engine)
{
  this->engine = engine;
  isUP = false;
  this->count = count;
  this->player = player;
  waittime = engine->getStopwatchElapsedSeconds();
  initAnimationSequence();
}

SeekerWaitState::~SeekerWaitState()
{
    engine = nullptr;
  std::cout<<"SeekerWaitState getting destroyed: isUP "<<isUP<<endl;
}

void SeekerWaitState::initAnimationSequence()
{
  sequence = initSeekerWaitAnimationSequence();
}

int SeekerWaitState::getCount()
{
    return count;
}

void SeekerWaitState::decrementCount()
{
    count--;
}

shared_ptr<vector<int> > SeekerWaitState::getWeights(AIPersonalityType personality) 
{
  shared_ptr<vector<int> > weights = make_shared<vector<int> >();
  (*(weights)) = jpcMap.find(personality)->second;
  return weights;
}

shared_ptr<vector<CommandType> > SeekerWaitState::getAllowedCommands()
{
  return SeekerWaitState::allowedCommands;
}

std::string SeekerWaitState::printState()
{
  std::cout<<"in found print state"<<endl;
  std::string print = "SeekerWait ";
  shared_ptr<Room> location = Room::roomIDMap->find(getLocationID())->second;
  print = print + to_string(count);
  
  std::cout<<"end of foundprint state"<<endl;
  return print;
}


void SeekerWaitState::displayState(Engine *engine, shared_ptr<Player> player)
{
  
  sequence->display(engine);
    
}





void SeekerWaitState::update(shared_ptr<Command> cmd, shared_ptr<stack<shared_ptr<RoleState> > > stateStack, shared_ptr<Player> player)
{
    switch(cmd->commandType)
    {
        case CONTINUE:
        case WAITANDCOUNT:
        {
            if(engine->getStopwatchElapsedSeconds() - waittime >= WAITSECONDS)
            {
                shared_ptr<RoleState> state = make_shared<SeekState>(player);
                state->setLocationID(this->getLocationID());
                stateStack->pop();
                stateStack->push(state);
            }
            else 
            {
                decrementCount();
            }
        }
        default:
        {
            break;
        }

    }
    
    
}

shared_ptr<AnimationSequence> SeekerWaitState::initSeekerWaitAnimationSequence()
{
  shared_ptr<AnimationSequence> standingseq = make_shared<AnimationSequence>();
  
    shared_ptr<DisplayObject> standingWithHandsUp = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);

    shared_ptr<DisplayObject> standingWithHandsDown = make_shared<DisplayObject>(player->getFilename(), player->getCenter()->x, player->getCenter()->y);

    standingseq->addImage(standingWithHandsUp);
    standingseq->addImage(standingWithHandsDown);
    return standingseq;
}


