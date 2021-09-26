#ifndef _AIPLAYER_H
#define _AIPLAYER_H
#include "Player.hpp"
#include "RoleState.hpp"


class AIPlayer : public Player 
{
public:

  _PLAYERCLONE(AIPlayer)

  AIPlayer();

  AIPersonalityType personality;

  virtual shared_ptr<Command> getCommand();

  virtual void initializePersonality(std::string type) override;

  virtual bool isAI() override;

  typedef shared_ptr<map<std::string, AIPersonalityType> >  PersonalityMap;
  static PersonalityMap pmap;

  static PersonalityMap initPMap()
  {
    PersonalityMap pm = make_shared<map<std::string, AIPersonalityType> >();
    (*pm)["careful"] = CAREFUL;
    (*pm)["fun"] = FUN;
    (*pm)["risky"] = RISKY;
    (*pm)["nutty"] = NUTTY;
    return pm;
  }

  static AIPersonalityType getPersonalityType(std::string type)
  {
    return AIPlayer::pmap->find(type)->second;
  }

  
};
#endif
